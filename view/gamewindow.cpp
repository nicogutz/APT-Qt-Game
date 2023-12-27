#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , controller(QSharedPointer<GameController>::create())
    , start_time(QDateTime::currentDateTime().toSecsSinceEpoch())
    , elapsed_seconds(0)
    , timer(new QTimer(this))
    , paused(0) {
    // SETUP UI CONTROLLER AND VIEW
    controller->setParent(this);
    ui->setupUi(this);

    // DEFAULT OPTIONS
    //    setStyleSheet("background-color: white;");
    ui->level_label->setText("Level: 1");
    ui->colour_mode->setChecked(true);
    ui->text_mode->setChecked(false);
    ui->graphical_mode->setChecked(false);

    // CHOOSE MODE: MANUAL OR AUTOMATIC
    QMessageBox modeBox;
    modeBox.setWindowTitle("Select Game Mode");
    modeBox.setText("Please select the game mode:");
    QPushButton *manualButton = modeBox.addButton("Manual", QMessageBox::AcceptRole);
    QPushButton *autoButton = modeBox.addButton("Automatic", QMessageBox::AcceptRole);
    modeBox.exec();
    if(modeBox.clickedButton() == manualButton) {
        controller->updateGameMode(GameController::Mode::Manual);
        ui->mode_label->setText("Mode: Manual");
        ui->manual->setChecked(true);
        ui->automatic->setChecked(false);
    } else if(modeBox.clickedButton() == autoButton) {
        controller->updateGameMode(GameController::Mode::Automatic);
        ui->mode_label->setText("Mode: Automatic");
        ui->automatic->setChecked(true);
        ui->manual->setChecked(false);
    }

    // START GAME
    controller->startGame();
    ui->graphicsView->setScene(controller->getView().data());
    ui->graphicsView->show();
    controller->show();

    // START TIMER
    timer->start(1000);

    setFocusPolicy(Qt::StrongFocus);

    // ZOOM
    ui->horizontalSlider->setMinimum(-30);
    ui->horizontalSlider->setMaximum(30);
    ui->horizontalSlider->setValue(0);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.0, 1.0);

    // SIGNALS AND SLOTS
    QObject::connect(timer, &QTimer::timeout, this, [this] {
        GameWindow::updateTime(true);
    });
    QObject::connect(ui->pause, &QPushButton::clicked, this, [this] { GameWindow::updateTime(false); });
    QObject::connect(ui->automatic, &QAction::changed, ui->manual, &QAction::toggle);
    QObject::connect(ui->manual, &QAction::changed, ui->automatic, &QAction::toggle);
    QObject::connect(ui->horizontalSlider, &QSlider::valueChanged, this, &GameWindow::zoomBySlider);

    connect(ui->graphical_mode, &QAction::triggered, this, &GameWindow::setGraphicalView);
    connect(ui->text_mode, &QAction::triggered, this, &GameWindow::setTextualView);
    connect(ui->colour_mode, &QAction::triggered, this, &GameWindow::setColorView);
}

void GameWindow::updateTime(bool active) {
    if(active) { // RESTARTING GAME
        if(paused == 0) { // first game never paused
            ui->pause->setText("Pause game");
            int currentTime = QDateTime::currentDateTime().toSecsSinceEpoch();
            elapsed_seconds = currentTime - start_time;
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");
            controller->updateGameState(GameController::State::Running);
        } else { // game restarting
            elapsed_seconds++;
            timer->start(1000);
            ui->pause->setText("Pause game");
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");

            controller->updateGameState(GameController::State::Running);
        }

    } else { // PAUSING GAME
        paused++;
        if(paused == 0) { // pausing for the first time
            ui->pause->setText("Resume game");
            timer->stop();
            controller->updateGameState(GameController::State::Paused);

        } else if(paused % 2 == 0) {
            elapsed_seconds++;
            timer->start(1000);
            ui->pause->setText("Pause game");
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");
            controller->updateGameState(GameController::State::Running);

        } else {
            ui->pause->setText("Resume game");
            timer->stop();
            controller->updateGameState(GameController::State::Paused);
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if(paused % 2 == 0) {
        switch(event->key()) {
        case Qt::Key_Up:
            controller->characterMove(Direction::Up);
            break;
        case Qt::Key_Down:
            controller->characterMove(Direction::Down);
            break;
        case Qt::Key_Left:
            controller->characterMove(Direction::Left);
            break;
        case Qt::Key_Right:
            controller->characterMove(Direction::Right);
            break;
        case Qt::Key_Space:
            controller->characterAtttack();
            break;
        default:
            QMainWindow::keyPressEvent(event); // Handle other key events
        }
    }
}

void GameWindow::processCommand() {
    ui->plainTextEdit->clear();
    QString command = ui->textEdit->text().trimmed().toLower(); // Normalize input
    if(command == "move left") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterMove(Direction::Left);
    } else if(command == "move right") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterMove(Direction::Right);
    } else if(command == "move up") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterMove(Direction::Up);
    } else if(command == "move down") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterMove(Direction::Down);
    } else if(command == "health pack") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterAtttack();
    } else if(command == "attack") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        controller->characterAtttack();
    } else if(command == "pause/resume") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        updateTime(false);
    } else if(command == "quit") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        QApplication::quit();
    } else if(command == "restart") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        QApplication::quit();
    } else if(command == "view") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
    } else if(command == "help") {
        showHelp();
    } else {
        showInvalidCommandMessage();
    }
    ui->textEdit->clear();
}

void GameWindow::showHelp() {
    QString helpMessage = "Available commands:\n"
                          "- move [direction]: Move the protagonist to the left/right/up/down\n"
                          "- pause/resume: Pause or resume the game\n"

                          "- view: Toggle between graphical and text view\n"
                          "- attack: Attack the nearest enemy\n"
                          "- health pack: Take a health pack\n"
                          "- quit: Quit the game\n"
                          "- restart= Restart game from scratch\n"
                          "Type 'help' to show this message again.";
    ui->plainTextEdit->setPlainText(helpMessage);
}

void GameWindow::showInvalidCommandMessage() {
    QString errorMessage = "Invalid command. Type 'help' for a list of possible commands.";
    ui->plainTextEdit->setPlainText(errorMessage);
}

void GameWindow::zoomBySlider(int value) {
    qreal scaleFactor = 1.0 + (value / 50.0);

    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(scaleFactor, scaleFactor);
}

void GameWindow::updateLevel(unsigned int level) {
    ui->level_label->setText("Level: " + QString::number(level));
}

void GameWindow::setGraphicalView() {
    controller->updateGameView(GameController::View::Graphical);
    ui->colour_mode->setChecked(false);
    ui->text_mode->setChecked(false);
    ui->graphical_mode->setChecked(true);
}
void GameWindow::setTextualView() {
    controller->updateGameView(GameController::View::Text);
    ui->colour_mode->setChecked(false);
    ui->text_mode->setChecked(true);
    ui->graphical_mode->setChecked(false);
}
void GameWindow::setColorView() {
    controller->updateGameView(GameController::View::Color);
    ui->colour_mode->setChecked(true);
    ui->text_mode->setChecked(false);
    ui->graphical_mode->setChecked(false);
}

// DESTRUCTOR

GameWindow::~GameWindow() {
    delete ui;
    delete timer;
}

/**TODO
 * view & mode menus
 * energy health show in gamewindow
 * add mode and view attributes to controller and connect menus to correct renderer
 * pathfinder
 * fix model create in factory and poison level
 */
