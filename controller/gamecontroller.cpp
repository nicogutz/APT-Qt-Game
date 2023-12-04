#include "gamecontroller.h"
#include <QGraphicsTextItem>
#include <iostream>


GameController::GameController()
    : QGraphicsView()
    , m_model()

    , m_view (QSharedPointer<GameView>::create(10,10))

{
    this->setScene(m_view.data());
    m_model.append(QSharedPointer<GameObjectModel>(new GameObjectModel()));
}



void GameController::characterMove(GameObject::Direction to)
{
    QString message = "hello";
    switch (to) {
    case GameObject::Direction::Up:
        message = "Character moved up";
        break;
    case GameObject::Direction::Bottom:
        message = "Character moved down";
        break;
    case GameObject::Direction::Left:
        message = "Character moved left";
        break;
    case GameObject::Direction::Right:
        message = "Character moved right";


    }


    QGraphicsTextItem* textItem = new QGraphicsTextItem(message);
    textItem->setPos(0, 0);

    m_view->addItem(textItem);
}

void GameController::characterAtttack(GameObject::Direction to)
{
    
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

