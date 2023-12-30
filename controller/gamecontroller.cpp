#include "gamecontroller.h"
#include "model/behaviors/attack.h"
#include "view/renderer/spriterenderer.h"
#include "view/renderer/textrenderer.h"
#include "view/renderer/colorrenderer.h"

#include <QCoreApplication>
#include <qdatetime.h>

GameController::GameController()
    : QGraphicsView()
    , m_gameLevel(0)
    , m_gameState(State::Running)
    , m_gameView(View::Sprite) {};

void GameController::startGame(unsigned int enemies, unsigned int health_packs) {
    m_view = QSharedPointer<GameView>::create(this);
    m_view->setRenderer(QSharedPointer<SpriteRenderer>::create());
    m_enemies = enemies;
    m_health_packs = health_packs;
    m_gameLevel = 0;
    emitLevelUpdates();

    createNewLevel(m_gameLevel);
    this->show();
}

void GameController::updateLevel(Direction direction) {
    int newLevel = (direction == Direction::Up) ? m_gameLevel + 1 : m_gameLevel - 1;

    if(newLevel < 0 || newLevel > m_models.size()) {
        qDebug() << "Invalid level change request. Current Level: " << m_gameLevel << ", Requested Level: " << newLevel;
        return;
    }

    disconnectCurrentModel();

    // Determine whether to create a new model or use an existing one
    if(newLevel + 1 > m_models.size()) {
        qDebug() << "Creating new model for level " << newLevel;
        createNewLevel(newLevel);
    } else {
        qDebug() << "Switching to existing model for level " << newLevel;
        auto *model = m_models[newLevel];
        if(!model) {
            qDebug() << "Error: Model is null at level " << newLevel;
            return;
        }
        m_gameLevel = newLevel;
        m_character = model->getObject(ObjectType::Protagonist).at(0);
        m_view->createScene(model->getAllData());
        connectCurrentModel();
    }

    emitLevelUpdates();
}

void GameController::createNewLevel(int level) {
    QString imagePath;
    int e;
    int hp;
    switch(level) {
    case 1:
        imagePath = ":/images/worldmap2.png";
        e = 10;
        hp = 8;
        break;
    case 2:
        imagePath = ":/images/worldmap.png";
        e = 14;
        hp = 9;
        break;
    case 3:
        imagePath = ":/images/worldmap2.png";
        e = 16;
        hp = 10;
        break;
    case 5:
        imagePath = ":/images/worldmap.png";
        e = 20;
        hp = 10;
        break;
    case 6:
        imagePath = ":/images/worldmap2.png";
        e = 26;
        hp = 8;
        break;
    default:
        imagePath = ":/images/worldmap.png";
        e = 26;
        hp = 5;
        break;
    }

    auto *model = factory.createModel(imagePath, e, hp, 0.5f, level);
    m_models.append(model);
    model->setParent(this);

    m_enemies = e;
    m_health_packs = hp;
    m_gameLevel = level;

    auto oldCharacter = m_character;
    m_character = model->getObject(ObjectType::Protagonist).at(0);

    if(oldCharacter) {
        m_character->setData(oldCharacter->getAllData().at(0));
    }

    m_view->createScene(model->getAllData());

    connectCurrentModel();
}

void GameController::disconnectCurrentModel() {
    auto *model = m_models[m_gameLevel];
    disconnect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    disconnect(this, &GameController::tick, model, &GameObjectModel::tick);
    disconnect(model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
}
void GameController::connectCurrentModel() {
    auto *model = m_models[m_gameLevel];
    connect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    connect(this, &GameController::tick, model, &GameObjectModel::tick);
    connect(model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
}

void GameController::emitLevelUpdates() {
    emit enemiesUpdated(m_enemies);
    emit healthPacksUpdated(m_health_packs);
    emit levelUpdated(m_gameLevel);
}

void GameController::dataChanged(QMap<DataRole, QVariant> objectData) {
    switch(objectData[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Protagonist:
        if(objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Energy) {
            updateEnergy();
        }

        if(objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Health) {
            updateHealth();
        }
        break;
    case ObjectType::Doorway:
        if(objectData[DataRole::Direction].value<Direction>() == Direction::Down) {
            updateLevel(Direction::Down); // go down a level
        }
        if(objectData[DataRole::Direction].value<Direction>() == Direction::Up) {
            updateLevel(Direction::Up); // go up a level
        }
        break;

    case ObjectType::PoisonEnemy:

        break;
    case ObjectType::HealthPack:

        break;
    default:
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

            QTime dieTime = QTime::currentTime().addMSecs(250);
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
    int protagonistEnergy = m_character->getData(DataRole::Energy).toInt();
    emit energyUpdated(protagonistEnergy);

    if(protagonistEnergy == 0) {
        m_gameState = State::GameOver;
        emit gameOver();
    }
}

void GameController::updateHealth() {
    int protagonistHealth = m_character->getData(DataRole::Health).toInt();
    emit healthUpdated(protagonistHealth);

    if(protagonistHealth == 0) {
        m_gameState = State::GameOver;
        emit gameOver();
    }
}

void GameController::characterMove(Direction to) {
    if(m_gameState == State::Running) {
        if(auto move = m_character->getBehavior<Movement>()) {
            move->stepOn(to);
            emit tick();
        }
    }
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
    auto data = m_models[m_gameLevel]->getAllData();
    QSharedPointer<Renderer> renderer;

    switch(view) {
    case View::Sprite:
        renderer = QSharedPointer<SpriteRenderer>::create();
        break;
    case View::Color:
        renderer = QSharedPointer<ColorRenderer>::create();
        break;
    case View::Text:
        renderer = QSharedPointer<TextRenderer>::create();
        break;
    }

    m_view->createScene(data, renderer);
    m_gameView = view;
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
