#include "gamecontroller.h"
#include <QGraphicsTextItem>
#include <iostream>


GameController::GameController()
    : QGraphicsView()
    //, m_model(new GameObjectModel())
    //, m_view(new GameView())
{
    
}


void GameController::characterMove(GameObject::Direction to)
{
    
}
/*
void GameController::characterMove(int dir)
{
    QString message = "hello";
    switch (dir) {
    case 0:
        message = "moving up";
        break;
    case 1:
        message = "moving down";
        break;
    case 2:
        message = "moving left";
        break;
    case 3:
        message = "moving right";
        break;

    }
    QGraphicsTextItem* textItem = new QGraphicsTextItem(message);

    textItem->setPos(this->sceneRect().center().x() - textItem->boundingRect().width() / 2, 10);
    this->scene()->addItem(textItem);
    m_view->addItem(textItem);

*/

void GameController::characterAtttack(GameObject::Direction to)
{
    
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

