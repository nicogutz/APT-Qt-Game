#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GameWindow)
    , m_controller(QSharedPointer<GameController>::create())
    , m_startTime(QDateTime::currentDateTime().toSecsSinceEpoch())
    , m_elapsedSeconds(0)
    , m_timer(new QTimer(this))
    , m_paused(0) {
    // SETUP UI CONTROLLER AND VIEW
    m_controller->setParent(this);
    m_ui->setupUi(this);

    // DEFAULT OPTIONS
    //    setStyleSheet("background-color: white;");
    this->setFixedSize(1000, 800);
    m_ui->level_label->setText("Level: 1");
    m_ui->colour_mode->setChecked(true);
    m_ui->text_mode->setChecked(false);
    m_ui->sprite_mode->setChecked(false);
    m_ui->health->setValue(100);
    m_ui->energy->setValue(100);

    // CHOOSE MODE: MANUAL OR AUTOMATIC
    QMessageBox modeBox;
    modeBox.setWindowTitle("Select Game Mode");
    modeBox.setText("Please select the game mode:");
    QPushButton *manualButton = modeBox.addButton("Manual", QMessageBox::AcceptRole);
    QPushButton *autoButton = modeBox.addButton("Automatic", QMessageBox::AcceptRole);
    modeBox.exec();
    if(modeBox.clickedButton() == manualButton) {
        m_controller->updateGameMode(GameController::Mode::Manual);
        m_ui->mode_label->setText("Mode: Manual");
        m_ui->manual->setChecked(true);
        m_ui->automatic->setChecked(false);
        m_ui->path_find_trigger->hide();
    } else if(modeBox.clickedButton() == autoButton) {
        m_controller->updateGameMode(GameController::Mode::Automatic);
        m_ui->mode_label->setText("Mode: Automatic");
        m_ui->automatic->setChecked(true);
        m_ui->manual->setChecked(false);
        m_ui->path_find_trigger->show();
    }

    // START GAME
    m_controller->startGame(6, 5);
    m_ui->enemies_label->setText("Enemies: 6");
    m_ui->health_packs->setText("Health packs: 5");
    m_ui->graphicsView->setScene(m_controller->getView().data());
    m_ui->graphicsView->show();
    m_controller->show();

    // START TIMER
    m_timer->start(1000);

    setFocusPolicy(Qt::StrongFocus);

    // ZOOM
    m_ui->horizontalSlider->setMinimum(-30);
    m_ui->horizontalSlider->setMaximum(30);
    m_ui->horizontalSlider->setValue(-30);

    // SIGNALS AND SLOTS
    QObject::connect(m_timer, &QTimer::timeout, this, [this] {
        GameWindow::updateTime(true);
    });
    QObject::connect(m_ui->pause, &QPushButton::clicked, this, [this] { GameWindow::updateTime(false); });
    QObject::connect(m_ui->automatic, &QAction::changed, m_ui->manual, &QAction::toggle);
    QObject::connect(m_ui->manual, &QAction::changed, m_ui->automatic, &QAction::toggle);
    QObject::connect(m_ui->horizontalSlider, &QSlider::valueChanged, this, &GameWindow::zoomBySlider);

    connect(m_ui->sprite_mode, &QAction::triggered, this, &GameWindow::setSpriteView);
    connect(m_ui->text_mode, &QAction::triggered, this, &GameWindow::setTextualView);
    connect(m_ui->colour_mode, &QAction::triggered, this, &GameWindow::setColorView);

    QObject::connect(m_ui->path_find_trigger, &QPushButton::clicked, m_controller.data(), &GameController::path_finder);

    QObject::connect(m_controller.data(), &GameController::energyUpdated, m_ui->energy, &QProgressBar::setValue);
    QObject::connect(m_controller.data(), &GameController::healthUpdated, m_ui->health, &QProgressBar::setValue);

    zoomBySlider(-30);
}

void GameWindow::updateTime(bool active) {
    if(active) { // RESTARTING GAME
        if(m_paused == 0) { // first game never paused
            m_ui->pause->setText("Pause game");
            int currentTime = QDateTime::currentDateTime().toSecsSinceEpoch();
            m_elapsedSeconds = currentTime - m_startTime;
            m_ui->time_label->setText("Elapsed time: " + QString::number(m_elapsedSeconds) + " s");
            m_controller->updateGameState(GameController::State::Running);
        } else { // game restarting
            m_elapsedSeconds++;
            m_timer->start(1000);
            m_ui->pause->setText("Pause game");
            m_ui->time_label->setText("Elapsed time: " + QString::number(m_elapsedSeconds) + " s");

            m_controller->updateGameState(GameController::State::Running);
        }

    } else { // PAUSING GAME
        m_paused++;
        if(m_paused == 0) { // pausing for the first time
            m_ui->pause->setText("Resume game");
            m_timer->stop();
            m_controller->updateGameState(GameController::State::Paused);

        } else if(m_paused % 2 == 0) {
            m_elapsedSeconds++;
            m_timer->start(1000);
            m_ui->pause->setText("Pause game");
            m_ui->time_label->setText("Elapsed time: " + QString::number(m_elapsedSeconds) + " s");
            m_controller->updateGameState(GameController::State::Running);

        } else {
            m_ui->pause->setText("Resume game");
            m_timer->stop();
            m_controller->updateGameState(GameController::State::Paused);
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if(m_paused % 2 == 0) {
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
        updateTime(false);
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
    m_ui->level_label->setText("Level: " + QString::number(level));
    m_controller->startGame(enemies, health_packs);
    m_ui->enemies_label->setText("Enemies: " + QString::number(enemies));
    m_ui->health_packs->setText("Health packs: " + QString::number(health_packs));
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

/**TODO
 * energy health show in gamewindow!!!!
 * pathfinder, fix it, add delay, add visualizzation, make enemies too strong
 * world inversed --> fix it
 * window size
 */
