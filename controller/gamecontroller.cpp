#include "gamecontroller.h"

GameController::GameController()
    : QGraphicsView()

    , m_model()
    , m_view(QSharedPointer<GameView>::create(100, 100))
    , game_level(1)
    , enemies(0)
    , health_packs(0)
    , energy(100)
    , health(100)
    , game_mode("Manual")
    , game_state(State::Running)

{
    // m_model.append(QSharedPointer<GameObjectModel>(new GameObjectModel()));
}

void GameController::updateGameState(State new_state) {
    if(game_state != new_state) {
        game_state = new_state;
        // emit stateChanged(new_state);
    }
}

void GameController::updateLevel(unsigned int level) {
    game_level = level;
    // emit levelChangedSig(level);
}

void GameController::characterMove(Direction to) {
    if(game_state != State::Paused) {
        QString message = "hello";
        switch(to) {
        case Direction::Up:
            message = "Character moved up";
            break;
        case Direction::Bottom:
            message = "Character moved down";
            break;
        case Direction::Left:
            message = "Character moved left";
            break;
        case Direction::Right:
            message = "Character moved right";
            break;
        default:
            message = "Other";
        }

        QGraphicsTextItem *textItem = new QGraphicsTextItem(message);
        textItem->setPos(0, 0);

        m_view->addItem(textItem);
    }
}

void GameController::characterAtttack(Direction to) {
    if(game_state != State::Paused) {
    }
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
