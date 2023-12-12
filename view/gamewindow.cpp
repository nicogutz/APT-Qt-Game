#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QTimer>
#include <iostream>
#include <QTime>
#include <qgraphicsitem.h>



GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , controller(QSharedPointer<GameController>::create())
    , start_time(QTime::currentTime().second())
    , elapsed_seconds(0)
    , timer (new QTimer(this))
    , paused (0)
{

    ui->setupUi(this);
    ui->graphicsView->setViewport(controller.data());
    ui->graphicsView->setScene(controller->getView().data());

    // SIGNALS AND SLOTS
    QObject::connect(timer, &QTimer::timeout, this, [this]{
        GameWindow::updateTime(true);
    });

    QObject::connect(ui->pause, &QPushButton::clicked, this, [this]{GameWindow::updateTime(false);});


    ui->graphicsView->show();
    controller->show();

    timer->start(1000);
    ui->level_label->setText("Level: 1");

    //setFocusPolicy(Qt::StrongFocus);



}


void GameWindow::updateTime(bool active) {


    if (active) { // RESTARTING GAME
        if (paused == 0){ // first game never paused
            ui->pause->setText("Pause game");
            int currentTime = QTime::currentTime().second();
            elapsed_seconds = currentTime - start_time;
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");
            controller->updateGameState(GameController::State::Running);
        }
        else{  // game restarting
            elapsed_seconds ++;
            timer->start(1000);
            ui->pause->setText("Pause game");
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");

            controller->updateGameState(GameController::State::Running);
        }



    } else { // PAUSING GAME
              paused ++;
        if (paused == 0){ // pausing for the first time
            ui->pause->setText("Restart game");
            timer->stop();
            controller->updateGameState(GameController::State::Paused);

        } else if (paused%2 == 0){
            elapsed_seconds ++;
            timer->start(1000);
            ui->pause->setText("Pause game");
            ui->time_label->setText("Elapsed time: " + QString::number(elapsed_seconds) + " s");
            controller->updateGameState(GameController::State::Running);

        } else {
            ui->pause->setText("Restart game");
            timer->stop();
            controller->updateGameState(GameController::State::Paused);
        }


    }
}

void GameWindow::updateLevel(unsigned int level){
    ui->level_label->setText("Level: " + QString::number(level));
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (paused%2 == 0){
        qDebug() << "Key Pressed";

        switch (event->key()) {
        case Qt::Key_Up:
            controller->characterMove(GameObject::Direction::Up);
            break;
        case Qt::Key_Down:
            controller->characterMove(GameObject::Direction::Bottom);
            break;
        case Qt::Key_Left:
            controller->characterMove(GameObject::Direction::Left);
            break;
        case Qt::Key_Right:
            controller->characterMove(GameObject::Direction::Right);
            break;
        default:
            QMainWindow::keyPressEvent(event);  // Handle other key events
        }
    }

}

void GameWindow::processCommand() {
    qDebug() << "processCommand() called";
    QString command = ui->textEdit->text().trimmed().toLower(); // Normalize input
    if (command == "move left") {
        controller->characterMove(GameObject::Direction::Left);
    } else if (command == "take health pack") {
        QGraphicsTextItem* textItem = new QGraphicsTextItem("taking health pack");
        controller->getView()->addItem(textItem);
    } else if (command == "pause game") {
        updateTime(false);
    } else if (command == "help") {
        showHelp();
    } else {
        showInvalidCommandMessage();
    }
    ui->textEdit->clear();
}

void GameWindow::showHelp() {
    QString helpMessage = "Available commands:\n"
                          "- move left: Move the protagonist to the left\n"
                          "- take health pack: Take a health pack\n"
                          "- pause game: Pause the game\n"
                          "- switch view: Toggle between graphical and text view\n"
                          "- attack enemy: Attack the nearest enemy\n"
                          "Type 'help' to show this message again.";
}

void GameWindow::showInvalidCommandMessage() {
    qDebug() << "showinvalidmes() called";
    QString errorMessage = "Invalid command. Type 'help' for a list of possible commands.";
    ui->plainTextEdit->setPlainText(errorMessage);

}


// GETTERS

QSharedPointer<GameController> GameWindow::getController(){
    return controller;
}

Ui::GameWindow* GameWindow::getUI(){
    return ui;
}

QTimer* GameWindow::getTimer(){
    return timer;
}


// DESTRUCTOR

GameWindow::~GameWindow()
{
    delete ui;
    delete timer;
}


/**TODO
* view & menu options only one checked at a time
* implement game menus
* implement command type
* convert timer to min/h
* connect controller variables (enemies, mode, health, energy etc)
* mode signal from window to controller and to label
* pathefinder?
* zoom
*/
