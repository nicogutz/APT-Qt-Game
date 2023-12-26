#include "gamecontroller.h"

GameController::GameController()
    : QGraphicsView()
    , m_gameMode("Manual")
    , m_gameState(State::Running)

{
    ObjectModelFactory factory;
    auto model = factory.createModel(":/images/worldmap.png", 6, 5, 0.5f);

//    // make protagonist
//    auto *obj = new GameObject(QMap<DataRole, QVariant>({
//      {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Protagonist)},
//      {DataRole::Health, 100},
//      {DataRole::Energy, 100.0f},
//      {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Right)},
//    }));
//    //    obj->setObjectName("Game_Protagonist");
//    obj->setBehavior<Movement>(QSharedPointer<GenericMoveBehavior>::create(obj));
//    obj->setBehavior<Poison>(QSharedPointer<GenericPoisonableBehavior>::create(obj));
//    obj->setParent(world[0][0]);
//    auto *model = new GameObjectModel(world);
//    model->setParent(this);
//    //    model->findChildren("Game_Protagonist");
    model->setParent(this);
    m_character = factory.getPro(); // this is temporary, could probably be done in a better ways
    m_model = QList<QPointer<GameObjectModel>>({model});
    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(model->getAllData(), QSharedPointer<ColorRenderer>::create());

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

/*
void GameController::executePathFinder() {
    auto path = factory.pathFinder();
    for (int move : path) {
        Direction direction;
        switch (move) {
        case 0: direction = Direction::Up; break;
        case 1: direction = Direction::TopRight; break;
        case 2: direction = Direction::Right; break;
        case 3: direction = Direction::BottomRight; break;
        case 4: direction = Direction::Down; break;
        case 5: direction = Direction::BottomLeft; break;
        case 6: direction = Direction::Left; break;
        case 7: direction = Direction::TopLeft; break;
        default:
            // Handle invalid move
            qDebug() << "Invalid move in path: " << move;
            continue;
        }
        characterMove(direction);
    }
}

*/
QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
