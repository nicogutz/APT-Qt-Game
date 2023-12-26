#include "gamecontroller.h"

GameController::GameController()
    : QGraphicsView()
    , m_gameMode("Manual")
    , m_gameState(State::Running)

{
    // create world grid
    ObjectModelFactory factory(":/images/worldmap.png", 0, 0, 0.0f);
    auto world = factory.createModel();
    // make protagonist
    auto *obj = new GameObject(QMap<DataRole, QVariant>({
      {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Protagonist)},
      {DataRole::Health, 100},
      {DataRole::Energy, 100.0f},
      {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Right)},
    }));
    //    obj->setObjectName("Game_Protagonist");
    obj->setBehavior<Movement>(QSharedPointer<GenericMoveBehavior>::create(obj));
    obj->setBehavior<Poison>(QSharedPointer<GenericPoisonableBehavior>::create(obj));
    obj->setParent(world[0][0]);
    auto *model = new GameObjectModel(world);
    model->setParent(this);
    //    model->findChildren("Game_Protagonist");

    m_character = obj;
    m_model = QList<QPointer<GameObjectModel>>({model});
    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(model->getAllData(), QSharedPointer<TextRenderer>::create());

    connect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);

    // factory.pathFinder();
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
        emit tick(0);
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
