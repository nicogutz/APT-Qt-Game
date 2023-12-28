#include "gamecontroller.h"
#include "model/behaviors/attack.h"
#include "view/renderer/spriterenderer.h"
#include "view/renderer/textrenderer.h"
#include "view/renderer/colorrenderer.h"

#include <QCoreApplication>
#include <qdatetime.h>

GameController::GameController()
    : QGraphicsView()
    , m_gameLevel(1)
    , m_gameState(State::Running)
    , m_gameView(View::Color) {};

void GameController::startGame(unsigned int enemies, unsigned int health_packs) {
    // create world with 6 Enemies 5 health packs and 3 PEnemies
    m_model = factory.createModel(":/images/worldmap.png", 20, 6, 0.5f);

    m_model->setParent(this);
    m_character = factory.getPro(); // this is temporary, could probably be done in a better ways

    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(m_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
    connect(m_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);

    connect(this, &GameController::tick, m_model, &GameObjectModel::tick);

    connect(m_character, &GameObject::dataChanged, this, &GameController::updateEnergy);
    connect(m_character, &GameObject::dataChanged, this, &GameController::updateHealth);
    this->show();
}

void GameController::path_finder() {
    if(m_gameState == State::Running) {
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

            QTime dieTime = QTime::currentTime().addMSecs(500);
            while(QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            QVariant protagonist_direction_variant = m_character->getData(DataRole::Direction);
            Direction protagonist_direction = protagonist_direction_variant.value<Direction>();
            if(direction != protagonist_direction) {
                characterMove(direction);
                characterMove(direction);
            } else {
                characterMove(direction);
            }
        }
    }
}

void GameController::updateEnergy() {
    QVariant protagonist_energy = m_character->getData(DataRole::Energy);
    int protagonist_energy_int = protagonist_energy.value<int>();
    emit energyUpdated(protagonist_energy_int);
}

void GameController::updateHealth() {
    QVariant protagonist_health = m_character->getData(DataRole::Health);
    int protagonist_health_int = protagonist_health.value<int>();
    emit healthUpdated(protagonist_health_int);
}

void GameController::characterMove(Direction to) {
    m_character->getBehavior<Movement>()->stepOn(to);
    emit tick();
}

void GameController::characterAtttack() {
    if(m_gameState == State::Running) {
        if(auto attack = m_character->getBehavior<Attack>()) {
            attack->attack();
            emit tick();
        }
    }
}

void GameController::setState(State new_state) {
    m_gameState = new_state;
}

void GameController::setLevel(unsigned int level) {
    m_gameLevel = level;
}
void GameController::updateGameView(View view) {
    m_gameView = view;
    if(view == View::Sprite) {
        m_view->createScene(m_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
    } else if(view == View::Text) {
        m_view->createScene(m_model->getAllData(), QSharedPointer<TextRenderer>::create());
    } else {
        m_view->createScene(m_model->getAllData(), QSharedPointer<ColorRenderer>::create());
    }
}

GameController::State GameController::getState() {
    return m_gameState;
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
