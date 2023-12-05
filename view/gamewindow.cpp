#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QTimer>
#include <iostream>
#include <QTime>



GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , controller(QSharedPointer<GameController>::create())
    , startTime(QTime::currentTime().second())
    , elapsedSeconds(0)
    , timer (new QTimer(this))
    , paused (0)
{

    ui->setupUi(this);
    ui->graphicsView->setViewport(controller.data());
    ui->graphicsView->setScene(controller->getView().data());


    ui->graphicsView->show();
    controller->show();


    QObject::connect(timer, &QTimer::timeout, this, [this]{
        updateTime(true);
    });
    timer->start(1000);



    QObject::connect(ui->pause, &QPushButton::clicked, this, [this]{updateTime(false);});



}


void GameWindow::updateTime(bool active) {
    if (active) { // RESTARTING GAME
        if (paused == 0){ // first game never paused
            ui->pause->setText("Pause game");
            int currentTime = QTime::currentTime().second();
            elapsedSeconds = (currentTime - startTime);
            ui->time_label->setText("Elapsed time: " + QString::number(elapsedSeconds) + " s");
        }
        else{  // game restarting
            timer->start(1000);
            ui->pause->setText("Pause game");
            int currentTime = QTime::currentTime().second();
            elapsedSeconds = (currentTime - startTime) + elapsedSeconds;
            ui->time_label->setText("Elapsed time: " + QString::number(elapsedSeconds) + " s");
        }


    } else { // PAUSING GAME
              paused ++;
        if (paused == 0){ // first game never paused
            ui->pause->setText("Restart game");
            timer->stop();

        } else if (paused%2 == 0){
            ui->pause->setText("Pause game");
            timer->start(1000);
            startTime = QTime::currentTime().second();
            int currentTime = QTime::currentTime().second();
            elapsedSeconds = (currentTime - startTime) + elapsedSeconds;
            ui->time_label->setText("Elapsed time: " + QString::number(elapsedSeconds) + " s");
        } else {
            ui->pause->setText("Restart game");
            timer->stop();
        }


    }
}


void GameWindow::keyPressEvent(QKeyEvent *event)
{
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



QSharedPointer<GameController> GameWindow::getController(){
    return controller;
}

GameWindow::~GameWindow()
{
    delete ui;
}


