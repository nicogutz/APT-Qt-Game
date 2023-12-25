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
    controller->setParent(this);
    // SETUP UI CONTROLLER AND VIEW
    ui->setupUi(this);
    ui->graphicsView->setScene(controller->getView().data());
    ui->graphicsView->show();
    controller->show();

    // START TIMER
    timer->start(1000);

    setFocusPolicy(Qt::StrongFocus);

    // DEFAULT OPTIONS
    setStyleSheet("background-color: #F4C2C2;");

    ui->level_label->setText("Level: 1");
    ui->graphical_mode->setChecked(true);
    ui->mode_label->setText("Mode: Manual");
    ui->manual->setChecked(true);

    ui->horizontalSlider->setMinimum(-30);
    ui->horizontalSlider->setMaximum(30);
    ui->horizontalSlider->setValue(-30);
    // SIGNALS AND SLOTS
    QObject::connect(timer, &QTimer::timeout, this, [this] {
        GameWindow::updateTime(true);
    });

    QObject::connect(ui->pause, &QPushButton::clicked, this, [this] { GameWindow::updateTime(false); });
    QObject::connect(ui->automatic, &QAction::changed, ui->manual, &QAction::toggle);
    QObject::connect(ui->manual, &QAction::changed, ui->automatic, &QAction::toggle);

    QObject::connect(ui->horizontalSlider, &QSlider::valueChanged, this, &GameWindow::zoomBySlider);

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

void GameWindow::updateLevel(unsigned int level) {
    ui->level_label->setText("Level: " + QString::number(level));
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
        QGraphicsTextItem *textItem = new QGraphicsTextItem("taking health pack");
        controller->getView()->addItem(textItem);
    } else if(command == "attack") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        QGraphicsTextItem *textItem = new QGraphicsTextItem("attacking enemy");
        controller->getView()->addItem(textItem);
    } else if(command == "pause/resume") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
        updateTime(false);
    } else if(command == "quit") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
    } else if(command == "restart") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
    } else if(command == "view") {
        ui->plainTextEdit->setPlainText("command executed: " + command);
    } else if(command == "mode") {
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
                          "- mode: Toggle between manual and automatic mode\n"
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
    // Assuming the slider's minimum value is 0 and the maximum is 100
    // You can map these to a reasonable zoom range
    qreal scaleFactor = 1.0 + (value / 50.0); // e.g., slider at middle (value 50) => scale factor of 1.0 (no zoom)

    // Reset the view scale to 1:1
    ui->graphicsView->resetTransform();
    // Apply the new scale transformation
    ui->graphicsView->scale(scaleFactor, scaleFactor);
}

// DESTRUCTOR

GameWindow::~GameWindow() {
    delete ui;
    delete timer;
}

/**TODO
 * view & mode menus
 * convert timer to min/h?
 * connect controller variables (enemies, mode, health, energy etc)
 * mode signal from window to controller and to label
 * pathefinder
 *
 *
 * energy health
 * path
 */
