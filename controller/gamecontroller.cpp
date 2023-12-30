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
    , m_gameView(View::Sprite) {};

void GameController::startGame(unsigned int enemies, unsigned int health_packs) {
    m_enemies = enemies; m_health_packs = health_packs; m_gameLevel = 1;
    emit enemiesUpdated(m_enemies);
    emit healthPacksUpdated(m_health_packs);
    emit levelUpdated(m_gameLevel);

    m_current_model = factory.createModel(":/images/worldmap.png", enemies, health_packs, 0.5f, m_gameLevel);
    m_models.append(m_current_model);
    m_current_model->setParent(this);
    m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);

    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
    connect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);

    connect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
    connect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);


    this->show();
}


//void GameController::updateLevel(Direction direction) {
//    m_gameLevel ++;
//    if (direction == Direction::Up){
//        if (m_gameLevel > (m_models.size()) ) {

//            disconnect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//            disconnect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//            disconnect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);

//            m_enemies = m_enemies+5 ; m_health_packs = m_health_packs+1;
//            emit enemiesUpdated(m_enemies);
//            emit healthPacksUpdated(m_health_packs);
//            emit levelUpdated(m_gameLevel);


//            m_current_model = factory.createModel(":/images/worldmap2.png", m_enemies, m_health_packs, 0.5f, m_gameLevel);
//            m_models.append(m_current_model);
//            m_current_model->setParent(this);

//            m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);
//            m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());


//            connect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//            connect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//            connect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
//        }
//        else {
//            disconnect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//            disconnect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//            disconnect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);

//            m_current_model = m_models[m_gameLevel-1];
//            m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);

//            m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
//            emit enemiesUpdated(m_enemies);
//            emit healthPacksUpdated(m_health_packs);
//            emit levelUpdated(m_gameLevel);
//            connect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//            connect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//            connect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);

//        }

//    } else if (direction == Direction::Down){

//        disconnect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//        disconnect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//        disconnect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);

//        m_gameLevel --;

//        m_current_model = m_models[1];

//        m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);
//        m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());

//        connect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
//        connect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
//        connect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);

//        emit enemiesUpdated(m_enemies);
//        emit healthPacksUpdated(m_health_packs);
//        emit levelUpdated(m_gameLevel);
//    }

//}

//************************************************************************************
void GameController::updateLevel(Direction direction) {

    int newLevel = (direction == Direction::Up) ? m_gameLevel + 1 : m_gameLevel - 1;
    if (newLevel < 1 || newLevel > m_models.size() + 1) {
        qDebug() << "Invalid level change request. Current Level: " << m_gameLevel << ", Requested Level: " << newLevel;
        return;
    }
    disconnectCurrentModel();
    // Determine whether to create a new model or use an existing one
    if (newLevel > m_models.size()) {
        qDebug() << "Creating new model for level " << newLevel;
        createNewLevel(newLevel);
    } else {
        qDebug() << "Switching to existing model for level " << newLevel;
        m_current_model = m_models[newLevel - 1];
        if (!m_current_model) {
            qDebug() << "Error: Model is null at level " << newLevel;
            return;
        }
        m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);
        m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
    }
    // Update game level and reconnect signals
    m_gameLevel = newLevel;
    connectCurrentModel();
    emitLevelUpdates();
}

void GameController::createNewLevel(int level) {
    QString imagePath; int e; int hp;
    switch (level) {
    case 2: imagePath = ":/images/worldmap2.png"; e=10; hp=8; break;
    case 3: imagePath = ":/images/worldmap.png"; e=14; hp=9; break;
    case 4: imagePath = ":/images/worldmap2.png"; e=16; hp=10; break;
    case 5: imagePath = ":/images/worldmap.png"; e=20; hp=10; break;
    case 6: imagePath = ":/images/worldmap2.png"; e=26; hp=8; break;
    default: imagePath = ":/images/worldmap.png"; e=26; hp=5; break;
    }

    m_current_model = factory.createModel(imagePath, e, hp, 0.5f, level);
    m_enemies = e; m_health_packs = hp;
    m_models.append(m_current_model);
    m_current_model->setParent(this);
    m_character = m_current_model->getObject(ObjectType::Protagonist).at(0);
    m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
}


void GameController::disconnectCurrentModel() {
    disconnect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    disconnect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
    disconnect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
}
void GameController::connectCurrentModel() {
    connect(m_current_model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    connect(this, &GameController::tick, m_current_model, &GameObjectModel::tick);
    connect(m_current_model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
}

void GameController::emitLevelUpdates() {
    emit enemiesUpdated(m_enemies);
    emit healthPacksUpdated(m_health_packs);
    emit levelUpdated(m_gameLevel);
}

//***********************************************************************************************

void GameController::dataChanged(QMap<DataRole, QVariant> objectData){
    switch(objectData[DataRole::Type].value<ObjectType>()){
    case ObjectType::Protagonist:
        if (objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Energy){
            updateEnergy();
        }

        if (objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Health){
            updateHealth();
        }
        break;
    case ObjectType::Doorway:
        if (objectData[DataRole::Direction].value<Direction>() == Direction::Down){
            if (m_gameLevel != 1){
                updateLevel(Direction::Down);// go down a level
            }

        }
        if
            (objectData[DataRole::Direction].value<Direction>() == Direction::Up){
                updateLevel(Direction::Up); // go up a level

            }
        break;

    case ObjectType::PoisonEnemy:

        break;
    case ObjectType::HealthPack:

        break;

    }
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




void GameController::updateGameView(View view) {
    m_gameView = view;
    if(view == View::Sprite) {
        m_view->createScene(m_current_model->getAllData(), QSharedPointer<SpriteRenderer>::create());
    } else if(view == View::Text) {
        m_view->createScene(m_current_model->getAllData(), QSharedPointer<TextRenderer>::create());
    } else {
        m_view->createScene(m_current_model->getAllData(), QSharedPointer<ColorRenderer>::create());
    }
}



void GameController::setState(State new_state) {
    m_gameState = new_state;
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
