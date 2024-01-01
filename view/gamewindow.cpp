#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GameWindow)
    , m_controller(QSharedPointer<GameController>::create())
    , m_startTime(QDateTime::currentDateTime().toSecsSinceEpoch())
    , m_elapsedSeconds(0)
    , m_timer(new QTimer(this)) {
    // SETUP UI CONTROLLER AND VIEW
    m_controller->setParent(this);
    m_ui->setupUi(this);
    initializeCommands();
    qApp->installEventFilter(this);

    // DEFAULT OPTIONS
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(true);
    m_ui->health->setValue(100);
    m_ui->energy->setValue(100);
    m_ui->lcdTime->display("00:00");
    m_ui->textEdit->hide();
    m_ui->plainTextEdit->hide();
    m_ui->type_command->hide();

    this->setFocusPolicy(Qt::StrongFocus);

    // ZOOM
    m_ui->horizontalSlider->setMinimum(-34);
    m_ui->horizontalSlider->setMaximum(30);
    m_ui->horizontalSlider->setValue(-34);
    zoomBySlider(-34);


    // CHOOSE MODE: MANUAL OR AUTOMATIC
    QMessageBox modeBox;
    modeBox.setWindowTitle("Select Game Mode");
    modeBox.setText("Please select the game mode:");
    QPushButton *manualButton = modeBox.addButton("Manual", QMessageBox::AcceptRole);
    QPushButton *autoButton = modeBox.addButton("Automatic", QMessageBox::AcceptRole);
    modeBox.exec();
    if(modeBox.clickedButton() == manualButton) {
        m_controller->setState(GameController::State::Running);
        m_ui->path_find_trigger->hide();
    } else if(modeBox.clickedButton() == autoButton) {
        m_controller->setState(GameController::State::Running);
        installEventFilter(this);
        m_ui->path_find_trigger->show();
    }

    // START GAME
    m_controller->startGame();
    m_ui->lcdHealth->display(4);
    m_ui->lcdEnemies->display(27);
    m_ui->lcdLevel->display(1);
    m_ui->graphicsView->setScene(m_controller->getView().data());
    m_ui->graphicsView->show();
    m_controller->show();

    // START TIMER
    m_timer->start(1000);


    // SIGNALS AND SLOTS
    QObject::connect(m_ui->textEdit, &QLineEdit::returnPressed, this, &GameWindow::processCommand);
    connect(m_timer, &QTimer::timeout, this, &GameWindow::updateTime);
    connect(m_ui->pause, &QPushButton::clicked, this, &GameWindow::togglePause);
    connect(m_ui->automatic, &QAction::changed, m_ui->manual, &QAction::toggle);
    connect(m_ui->manual, &QAction::changed, m_ui->automatic, &QAction::toggle);
    connect(m_ui->horizontalSlider, &QSlider::valueChanged, this, &GameWindow::zoomBySlider);
    connect(m_controller.data(), &GameController::levelUpdated, this, [this](int level) {
        zoomBySlider(-34);
    });
    connect(m_ui->sprite_mode, &QAction::triggered, this, &GameWindow::setSpriteView);
    connect(m_ui->text_mode, &QAction::triggered, this, &GameWindow::setTextualView);
    connect(m_ui->colour_mode, &QAction::triggered, this, &GameWindow::setColorView);
    connect(m_ui->path_find_trigger, &QPushButton::clicked, m_controller.data(), &GameController::path_finder);
    connect(m_controller.data(), &GameController::energyUpdated, m_ui->energy, &QProgressBar::setValue);
    connect(m_controller.data(), &GameController::healthUpdated, m_ui->health, &QProgressBar::setValue);
    connect(m_controller.data(), &GameController::enemiesUpdated, this, [this](unsigned int enemies) {
        m_ui->lcdEnemies->display((int)(enemies));
    });
    connect(m_controller.data(), &GameController::healthPacksUpdated, this, [this](unsigned int healthPacks) {
        m_ui->lcdHealth->display((int)(healthPacks));
    });
    connect(m_controller.data(), &GameController::levelUpdated, this, [this](unsigned int level) {
        m_ui->lcdLevel->display((int)(level + 1));
    });
    connect(m_controller.data(), &GameController::gameOver, this, &GameWindow::gameOver);

}
void GameWindow::togglePause() {
    if(m_controller->getState() == GameController::State::Paused) {
        connect(m_timer, &QTimer::timeout, this, &GameWindow::updateTime);
        m_controller->setState(GameController::State::Running);
        m_ui->pause->setText("Pause Game");
    } else {
        disconnect(m_timer, &QTimer::timeout, this, &GameWindow::updateTime);
        m_controller->setState(GameController::State::Paused);
        m_ui->pause->setText("Resume Game");
    }
}
void GameWindow::updateTime() {
    m_elapsedSeconds++;
    m_ui->lcdTime->display(QDateTime::fromSecsSinceEpoch(m_elapsedSeconds).toUTC().toString("mm:ss"));
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if(m_controller->getState() == GameController::State::Running &&
        m_controller->getGameView() != GameController::View::Text) {
        switch(event->key()) {
        case Qt::Key_Up:
            m_controller->characterMove(Direction::Up);
            break;
        case Qt::Key_Down:
            m_controller->characterMove(Direction::Down);
            break;
        case Qt::Key_Left:
            m_controller->characterMove(Direction::Left);
            break;
        case Qt::Key_Right:
            m_controller->characterMove(Direction::Right);
            break;
        case Qt::Key_Space:
            m_controller->characterAtttack();
            break;
        default:
            QMainWindow::keyPressEvent(event);
        }
    }
}



void GameWindow::initializeCommands() {
    // Move commands
    moveCommands["l"] = { [this]() { m_controller->characterMove(Direction::Left); }, "Move Left" };
    moveCommands["r"] = { [this]() { m_controller->characterMove(Direction::Right); }, "Move Right" };
    moveCommands["u"] = { [this]() { m_controller->characterMove(Direction::Up); }, "Move Up" };
    moveCommands["d"] = { [this]() { m_controller->characterMove(Direction::Down); }, "Move Down" };
    moveCommands["a"] = { [this]() { m_controller->characterAtttack(); }, "Attack" };

    // View commands
    viewCommands["t"] = { [this]() { setTextualView(); }, "Switch to Textual View" };
    viewCommands["c"] = { [this]() { setColorView(); }, "Switch to Color View" };
    viewCommands["s"] = { [this]() { setSpriteView(); }, "Switch to Sprite View" };

    // Game commands
    gameCommands["q"] = { [this]() { QApplication::quit(); }, "Quit Game" };
    gameCommands["p"] = { [this]() { togglePause(); }, "Pause/Resume Game" };
    gameCommands["r"] = { [this]() {
                             QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
                             QApplication::quit();
                         }, "Restart Game" };

    // Zoom commands
    zoomCommands["+"] = { [this]() {
                             int maxZoom = m_ui->horizontalSlider->maximum();
                             m_ui->horizontalSlider->setValue(maxZoom);
                             zoomBySlider(maxZoom);
                         }, "Zoom In" };
    zoomCommands["-"] = { [this]() {
                             int minZoom = m_ui->horizontalSlider->minimum();
                             m_ui->horizontalSlider->setValue(minZoom);
                             zoomBySlider(minZoom);
                         }, "Zoom Out" };
}

void GameWindow::processCommand() {
    QString errorMessage = "Invalid command. Type '?' for a list of possible commands.";
    QString command = m_ui->textEdit->text().trimmed().toLower();

    if (command == '?') {
        showHelp();
    } else {
        QStringList commandParts = command.split(' ');

        if (commandParts.size() == 2) {
            QString commandType = commandParts[0];
            QString commandAction = commandParts[1];

            if (commandType == "move" && moveCommands.contains(commandAction)) {
                moveCommands[commandAction].first();
            } else if (commandType == "view" && viewCommands.contains(commandAction)) {
                viewCommands[commandAction].first();
            } else if (commandType == "game" && gameCommands.contains(commandAction)) {
                gameCommands[commandAction].first();
            } else if (commandType == "zoom" && zoomCommands.contains(commandAction)) {
                zoomCommands[commandAction].first();
            } else {
                m_ui->plainTextEdit->setPlainText(errorMessage);
            }
        } else {
            m_ui->plainTextEdit->setPlainText(errorMessage);
        }
    }
    m_ui->textEdit->clear();
}

void GameWindow::showHelp() {
    QString helpMessage = "Available commands:\n";
    // Move Commands
    helpMessage += "\nMove Commands:\n";
    for (const auto &cmd : moveCommands.keys()) {
        helpMessage += "move " + cmd + " - " + moveCommands[cmd].second + "\n";
    }
    // View Commands
    helpMessage += "\nView Commands:\n";
    for (const auto &cmd : viewCommands.keys()) {
        helpMessage += "view " + cmd + " - " + viewCommands[cmd].second + "\n";
    }
    // Game Commands
    helpMessage += "\nGame Commands:\n";
    for (const auto &cmd : gameCommands.keys()) {
        helpMessage += "game " + cmd + " - " + gameCommands[cmd].second + "\n";
    }
    // Zoom Commands
    helpMessage += "\nZoom Commands:\n";
    for (const auto &cmd : zoomCommands.keys()) {
        helpMessage += "zoom " + cmd + " - " + zoomCommands[cmd].second + "\n";
    }
    m_ui->plainTextEdit->setPlainText(helpMessage);
}



void GameWindow::zoomBySlider(int value) {
    qreal scaleFactor = 1.0 + (value / 50.0);
    m_ui->graphicsView->resetTransform();
    m_ui->graphicsView->scale(scaleFactor, scaleFactor);
}



void GameWindow::updateLevel(unsigned int level, unsigned int enemies, unsigned int health_packs) {
    m_ui->lcdLevel->display((int)level);
    m_controller->startGame();
    m_ui->lcdEnemies->display((int)enemies);
    m_ui->lcdHealth->display((int)health_packs);
}

void GameWindow::setSpriteView() {
    m_controller->updateGameView(GameController::View::Sprite);
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(true);
    m_ui->textEdit->hide();
    m_ui->plainTextEdit->hide();
    m_ui->type_command->hide();
}
void GameWindow::setTextualView() {
    m_controller->updateGameView(GameController::View::Text);
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(true);
    m_ui->sprite_mode->setChecked(false);
    m_ui->textEdit->show();
    m_ui->plainTextEdit->show();
    m_ui->type_command->show();
}
void GameWindow::setColorView() {
    m_controller->updateGameView(GameController::View::Color);
    m_ui->colour_mode->setChecked(true);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(false);
    m_ui->textEdit->hide();
    m_ui->plainTextEdit->hide();
    m_ui->type_command->hide();
}



bool GameWindow::eventFilter(QObject *watched, QEvent *event) {
    if (m_controller->getGameView() != GameController::View::Text){
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            keyPressEvent(keyEvent);
            return true;
        }
        return QMainWindow::eventFilter(watched, event);
    }
    return false;
}


void GameWindow::gameOver() {
    QString summary;
    summary += "Game Summary:\n";
    summary += "Level Reached: " + QString::number(m_ui->lcdLevel->intValue()) + "\n";
    summary += "Final Health: " + QString::number(m_ui->health->value()) + "\n";
    summary += "Final Energy: " + QString::number(m_ui->energy->value()) + "\n";

    QString totalTime = QString::number(m_elapsedSeconds);
    summary += "Total Time: " + totalTime + " seconds\n";

    QString gameOverText = "Game Over\nThanks for playing!\n\n" + summary;

    QMessageBox gameOverBox;
    gameOverBox.setWindowTitle("Game Over");
    gameOverBox.setText(gameOverText);

    QAbstractButton *playAgainButton = gameOverBox.addButton("Play Again", QMessageBox::YesRole);
    QAbstractButton *quitButton = gameOverBox.addButton("Quit", QMessageBox::NoRole);

    gameOverBox.exec();

    if(gameOverBox.clickedButton() == playAgainButton) {
        QCoreApplication::quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    } else if(gameOverBox.clickedButton() == quitButton) {
        QApplication::quit();
    }
}


// DESTRUCTOR

GameWindow::~GameWindow() {
    delete m_ui;
    delete m_timer;
}

