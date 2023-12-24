#include "gamecontroller.h"
#include "model/behaviors/concrete/movement/poisononstepbehavior.h"
#include "model/behaviors/concrete/movement/genericmovebehavior.h"
#include "model/behaviors/behaviors.h"
#include "view/renderer/textrenderer.h"
#include <view/renderer/colorrenderer.h>
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>

GameController::GameController()
    : QGraphicsView()
    , m_gameMode("Manual")
    , m_gameState(State::Running)

{
    // TODO: This is very much temporary
    QList<QList<QPointer<GameObject>>> world(10);
    QMap<DataRole, QVariant> tileData({{DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Tile)}});
    for(int i = 0; i < 10; ++i) {
        world[i] = QList<QPointer<GameObject>>(10);
        for(int j = 0; j < 10; ++j) {
            auto *obj = new GameObject(tileData);
            obj->setData(DataRole::Energy, (i + 1) * (50 / 10) + (j + 1) * (50 / 10));

            obj->setData(DataRole::Position, QPoint(i, j));
            obj->setBehavior<Movement>(QSharedPointer<PoisonOnStepBehavior>::create(obj));
            obj->setBehavior<Poison>(QSharedPointer<GenericPoisoningBehavior>::create(obj));
            world[i][j] = obj;
        }
    }
    auto *obj = new GameObject(QMap<DataRole, QVariant>({
      {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Protagonist)},
      {DataRole::Health, 89},
      {DataRole::Energy, 20},
      {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Right)},
    }));
    obj->setBehavior<Movement>(QSharedPointer<GenericMoveBehavior>::create(obj));
    obj->setBehavior<Poison>(QSharedPointer<GenericPoisonableBehavior>::create(obj));

    obj->setParent(world[0][0]);
    auto *model = new GameObjectModel(world);
    model->setParent(this);

    m_character = obj;
    m_model = QList<QPointer<GameObjectModel>>({model});
    m_view = QSharedPointer<GameView>::create(10, 10, this);

    m_view->createScene(model->getAllData(), QSharedPointer<TextRenderer>::create());

    connect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);

    this->show();
}

void GameController::updateGameState(State new_state) {
    if(m_gameState != new_state) {
        m_gameState = new_state;
        // emit stateChanged(new_state);
    }
}

void GameController::updateLevel(unsigned int level) {
    m_gameLevel = level;
    // emit levelChangedSig(level);
}

void GameController::characterMove(Direction to) {
    if(m_gameState != State::Paused) {
        m_character->getBehavior<Movement>()->stepOn(to);
    }
}

void GameController::characterAtttack() {
    if(m_gameState != State::Paused) {
        auto attack = m_character->getBehavior<Attack>();
        if(attack) {
            attack->attack();
        }
    }
}

QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
