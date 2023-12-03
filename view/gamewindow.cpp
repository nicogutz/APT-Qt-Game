#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <iostream>



GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , controller(new GameController())
{

    ui->setupUi(this);
    ui->graphicsView->setScene(controller->getView().data());
    ui->graphicsView->setViewport(controller);


    this->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    controller->setFocusPolicy(Qt::StrongFocus);
    controller->setFocus();

    ui->graphicsView->show();
    controller->show();

}

GameWindow::~GameWindow()
{
    delete controller;
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{

    std::cout << "hello";
    switch (event->key()) {
    case Qt::Key_Up:
        controller->characterMove(0);
        break;
    case Qt::Key_Down:
        controller->characterMove(1);
        break;
    case Qt::Key_Left:
        controller->characterMove(2);
        break;
    case Qt::Key_Right:
        controller->characterMove(3);
        break;
    }
}


