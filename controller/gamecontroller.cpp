#include "gamecontroller.h"
#include "model/behaviors/attack.h"

#include <model/behaviors/health.h>

GameController::GameController()
    : QGraphicsView()
    , m_gameLevel(1)
    , m_gameMode(Mode::Manual)
    , m_gameState(State::Running)
    , m_gameView(View::Color)

{
}

void GameController::startGame(unsigned int enemies, unsigned int health_packs) {

    // create world with 6 Enemies 5 health packs and 3 PEnemies
    m_model = factory.createModel(":/images/worldmap.png", 6, 5, 0.5f);

    m_model->setParent(this);
    m_character = factory.getPro(); // this is temporary, could probably be done in a better ways

    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(m_model->getAllData(), QSharedPointer<ColorRenderer>::create());
    connect(m_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    this->show();

}

void GameController::path_finder(){
    if(m_gameMode == Mode::Automatic) {
        auto path = factory.pathFinder();

        for(int move : path) {
            Direction direction;
            switch(move) {
            case 0: direction = Direction::Up; break;
            case 1: direction = Direction::TopLeft; break;
            case 2: direction = Direction::Left; break;
            case 3: direction = Direction::BottomLeft; break;
            case 4: direction = Direction::Down; break;
            case 5: direction = Direction::BottomRight; break;
            case 6: direction = Direction::Right; break;
            case 7: direction = Direction::TopRight; break;
            default:
                // Handle invalid move
                qDebug() << "Invalid move in path: " << move;
                continue;
            }
            characterMoveAuto(direction);
        }
    }
}
void GameController::characterMoveAuto(Direction to){
    if(m_gameState != State::Paused && m_gameView != View::Text) {
        m_character->getBehavior<Movement>()->stepOn(to);
        emit tick(0);
    }
}

void GameController::characterMove(Direction to) {
    if(m_gameState != State::Paused && m_gameMode != Mode::Automatic) {
        m_character->getBehavior<Movement>()->stepOn(to);
        emit tick(0);
    }
}

void GameController::characterAtttack() {
    if(m_gameState != State::Paused) {
        if(auto attack = m_character->getBehavior<Attack>()) {
            attack->attack();
        }
    }
}

void GameController::characterHealth() {
    if(m_gameState != State::Paused) {
        auto health = m_character->getBehavior<Health>();
    }
}

void GameController::updateGameState(State new_state) {
    if(m_gameState != new_state) {
        m_gameState = new_state;
    }
}

void GameController::updateLevel(unsigned int level) {
    m_gameLevel = level;
}
void GameController::updateGameView(View view) {
    m_gameView = view;
    if(view == View::Sprite) {
    } else if(view == View::Text) {
        m_view->createScene(m_model->getAllData(), QSharedPointer<TextRenderer>::create());
    } else {
        m_view->createScene(m_model->getAllData(), QSharedPointer<ColorRenderer>::create());
    }
}

void GameController::updateGameMode(Mode mode) {
    m_gameMode = mode;
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
