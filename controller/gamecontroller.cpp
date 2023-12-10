#include "gamecontroller.h"
#include <QGraphicsTextItem>
#include <iostream>



GameController::GameController()
    : QGraphicsView()

    , m_model()
    , m_view (QSharedPointer<GameView>::create(10,10))
    , game_level(1)
    , enemies(0)
    , health_packs(0)
    , energy (100)
    , health(100)
    , game_mode("Manual")

{
    this->setScene(m_view.data());

    m_model.append(QSharedPointer<GameObjectModel>(new GameObjectModel()));

}


void GameController::levelChanged(unsigned int level){
    game_level = level;
    //emit levelChangedSig(level);

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
        break;
    default:
            message = "Other";
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

