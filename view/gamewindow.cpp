#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QTimer>
#include <iostream>
#include <QTime>



GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , controller(QSharedPointer<GameController>::create())
{

    ui->setupUi(this);
    ui->graphicsView->setViewport(controller.data());
    ui->graphicsView->setScene(controller->getView().data());

    ui->graphicsView->show();
    controller->show();




}

void GameWindow::updateTime() {
    QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &GameWindow::updateTime);
    timer->start(1000);
    QTime startTime = QTime::currentTime();

    int elapsedSeconds = startTime.secsTo(QTime::currentTime());
    QTime time(0,0);
    time = time.addSecs(elapsedSeconds);
    ui->time_label->setText(time.toString("hh:mm:ss"));
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


