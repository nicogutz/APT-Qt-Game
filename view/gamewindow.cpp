#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QDateTime>

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

    // DEFAULT OPTIONS
    //    setStyleSheet("background-color: white;");
    //    this->setFixedSize(1000, 800);
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(true);
    m_ui->health->setValue(100);
    m_ui->energy->setValue(100);
    m_ui->lcdLevel->display(1);

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
    m_controller->startGame(6, 7); m_ui->lcdHealth->display(7); m_ui->lcdEnemies->display(6);
    m_ui->graphicsView->setScene(m_controller->getView().data());
    m_ui->graphicsView->show();
    m_controller->show();
    m_ui->lcdTime->display("00:00");

    // START TIMER
    m_timer->start(1000);

    setFocusPolicy(Qt::StrongFocus);

    // ZOOM
    m_ui->horizontalSlider->setMinimum(-30);
    m_ui->horizontalSlider->setMaximum(30);
    m_ui->horizontalSlider->setValue(-30);

    // SIGNALS AND SLOTS
    connect(m_timer, &QTimer::timeout, this, &GameWindow::updateTime);
    connect(m_ui->pause, &QPushButton::clicked, this, &GameWindow::togglePause);
    connect(m_ui->automatic, &QAction::changed, m_ui->manual, &QAction::toggle);
    connect(m_ui->manual, &QAction::changed, m_ui->automatic, &QAction::toggle);
    connect(m_ui->horizontalSlider, &QSlider::valueChanged, this, &GameWindow::zoomBySlider);

    connect(m_ui->sprite_mode, &QAction::triggered, this, &GameWindow::setSpriteView);
    connect(m_ui->text_mode, &QAction::triggered, this, &GameWindow::setTextualView);
    connect(m_ui->colour_mode, &QAction::triggered, this, &GameWindow::setColorView);

    connect(m_ui->path_find_trigger, &QPushButton::clicked, m_controller.data(), &GameController::path_finder);

    connect(m_controller.data(), &GameController::energyUpdated, m_ui->energy, &QProgressBar::setValue);
    connect(m_controller.data(), &GameController::healthUpdated, m_ui->health, &QProgressBar::setValue);

    connect(m_controller.data(), &GameController::enemiesUpdated, this, [this](unsigned int enemies) {
        m_ui->lcdEnemies->display(static_cast<int>(enemies));
    });
    connect(m_controller.data(), &GameController::healthPacksUpdated, this, [this](unsigned int healthPacks) {
        m_ui->lcdHealth->display(static_cast<int>(healthPacks));
    });

    connect(m_controller.data(), &GameController::levelUpdated, this, [this](unsigned int level) {
        m_ui->lcdLevel->display(static_cast<int>(level));
    });




    zoomBySlider(-30);
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
    if(m_controller->getState() == GameController::State::Running) {
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
            QMainWindow::keyPressEvent(event); // Handle other key events
        }
    }
}

void GameWindow::processCommand() {
    m_ui->plainTextEdit->clear();
    QString command = m_ui->textEdit->text().trimmed().toLower(); // Normalize input
    if(command == "move left") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterMove(Direction::Left);
    } else if(command == "move right") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterMove(Direction::Right);
    } else if(command == "move up") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterMove(Direction::Up);
    } else if(command == "move down") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterMove(Direction::Down);
    } else if(command == "health pack") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterAtttack();
    } else if(command == "attack") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_controller->characterAtttack();
    } else if(command == "pause") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        togglePause();
    } else if(command == "quit") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        QApplication::quit();
    } else if(command == "restart") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        QApplication::quit();
    } else if(command == "view text") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        setTextualView();
    } else if(command == "view color") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        setColorView();
    } else if(command == "view sprite") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        setSpriteView();
    } else if(command == "zoom in") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_ui->horizontalSlider->setValue(m_ui->horizontalSlider->maximum());
        zoomBySlider(m_ui->horizontalSlider->maximum());
    } else if(command == "zoom out") {
        m_ui->plainTextEdit->setPlainText("command executed: " + command);
        m_ui->horizontalSlider->setValue(m_ui->horizontalSlider->minimum());
        zoomBySlider(m_ui->horizontalSlider->minimum());
    } else if(command == "help") {
        showHelp();
    } else {
        showInvalidCommandMessage();
    }
    m_ui->textEdit->clear();
}

void GameWindow::showHelp() {
    QString helpMessage = "Available commands:\n"
                          "- move [left/right/up/down]: Move the protagonist\n"
                          "- attack: Attack the nearest enemy\n"
                          "- health pack: Take a health pack\n"
                          "- pause: Toggle between Pause and Resume the game\n"
                          "- view [text/color/sprite]: Switch views\n"
                          "- zoom [in/out]: Zoom in and out\n"
                          "- quit: Quit the game\n"
                          "- restart: Restart game from scratch\n"
                          "Type 'help' to show this message again.";
    m_ui->plainTextEdit->setPlainText(helpMessage);
}

void GameWindow::showInvalidCommandMessage() {
    QString errorMessage = "Invalid command. Type 'help' for a list of possible commands.";
    m_ui->plainTextEdit->setPlainText(errorMessage);
}

void GameWindow::zoomBySlider(int value) {
    qreal scaleFactor = 1.0 + (value / 50.0);

    m_ui->graphicsView->resetTransform();
    m_ui->graphicsView->scale(scaleFactor, scaleFactor);
}

void GameWindow::updateLevel(unsigned int level, unsigned int enemies, unsigned int health_packs) {
    m_ui->lcdLevel->display((int)level);
    m_controller->startGame(enemies, health_packs);
    m_ui->lcdEnemies->display((int)enemies);
    m_ui->lcdHealth->display((int)health_packs);
}

void GameWindow::setSpriteView() {
    m_controller->updateGameView(GameController::View::Sprite);
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(true);
}
void GameWindow::setTextualView() {
    m_controller->updateGameView(GameController::View::Text);
    m_ui->colour_mode->setChecked(false);
    m_ui->text_mode->setChecked(true);
    m_ui->sprite_mode->setChecked(false);
}
void GameWindow::setColorView() {
    m_controller->updateGameView(GameController::View::Color);
    m_ui->colour_mode->setChecked(true);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(false);
}

// DESTRUCTOR

GameWindow::~GameWindow() {
    delete m_ui;
    delete m_timer;
}


bool GameWindow::eventFilter(QObject *watched, QEvent *event) {
    if(event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(watched, event);
    }
}
