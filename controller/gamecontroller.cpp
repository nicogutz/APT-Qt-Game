#include "gamecontroller.h"

#include <model/behaviors/movement.h>

#include <node.h>

GameController::GameController()
    : QGraphicsView()
    , m_gameLevel(0)
    , m_gameState(State::Running)
    , m_gameView(View::Sprite) {};

void GameController::startGame() {
    m_view = QSharedPointer<GameView>::create(this); // Instantiate the GameView
    m_view->setRenderer(QSharedPointer<SpriteRenderer>::create()); // Instantiate and set the default renderer
    createNewLevel(m_gameLevel); // Create first level
    this->show();
}

void GameController::updateLevel(Direction direction) {
    int newLevel = (direction == Direction::Up) ? m_gameLevel + 1 : m_gameLevel - 1; // Check whether we go level up or level down

    // Invalid level
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
        auto *model = m_models[newLevel].first;
        if(!model) {
            qDebug() << "Error: Model is null at level " << newLevel;
            return;
        }

        m_gameLevel = newLevel;
        m_enemies = 10 * (m_gameLevel + 1) + 25;
        m_health_packs = 5 - (m_gameLevel / 3);

        m_character = model->getObject(ObjectType::Protagonist).at(0);
        m_view->createScene(model->getAllData());
        connectCurrentModel();
    }

    // Signal changes to the window
    emitLevelUpdates();
}

void GameController::createNewLevel(int level) {
    // Set the level parameters
    m_gameLevel = level;
    m_enemies = 10 * (level + 1) + 25;
    m_health_packs = 5 - (level / 3);
    // Call the model factory to generate model
    auto *model = ObjectModelFactory::createModel(m_enemies, m_health_packs, 0.5f, m_gameLevel);
    m_models.append({model, std::vector<Node>()});
    model->setParent(this);
    // Set the character aka protagonist
    auto oldCharacter = m_character;
    m_character = model->getObject(ObjectType::Protagonist).at(0);

    if(oldCharacter) {
        m_character->setData(oldCharacter->getAllData().at(0));
    }

    // Create new scene
    m_view->createScene(model->getAllData());
    connectCurrentModel(); // Reconnect new model
    emitLevelUpdates(); // Signal changes to the window
}

void GameController::disconnectCurrentModel() {
    auto *model = m_models[m_gameLevel].first;
    disconnect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    disconnect(this, &GameController::tick, model, &GameObjectModel::tick);
    disconnect(model, &GameObjectModel::dataChanged, this, &GameController::dataChanged);
}
void GameController::connectCurrentModel() {
    auto *model = m_models[m_gameLevel].first;
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
    // Filter the changes based on their type
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
            if(m_gameLevel != 0) {
                updateLevel(Direction::Down); // go down a level
            }
        }
        if(objectData[DataRole::Direction].value<Direction>() == Direction::Up) {
            updateLevel(Direction::Up); // go up a level
        }
        break;
    default:
        break;
    }
}

void GameController::pathFinder(int x, int y) {

    auto data = m_models[m_gameLevel].first->getAllData(false); // Get current model data
    std::vector<Node> nodes; // Node class for the pathfinder

    int rows = m_models[m_gameLevel].first->getRowCount();
    int cols = m_models[m_gameLevel].first->getColumnCount();

    for(const auto &row : data) {
        for(const auto &obj : row) {

            nodes.emplace_back(obj); // Insert model tiles into nodes
        }
    }

    // Get protagonist position in the world = start position of the pathfinder
    auto pos = static_cast<GameObject *>(m_character->parent())->getData(DataRole::Position).toPoint();

    Comparator<Node> comp = [](const Node &a, const Node &b) {
        return a.h > b.h;
    };

    // Check for non valid input position
    if(x >= rows || y >= cols || x < 0 || y < 0) {
         y = cols - 1;
         x = rows - 1;
    }
    auto* start = &nodes[rows * pos.y() + pos.x()];
    auto* dest = &nodes[rows * y + x];
    PathFinder<Node, Node> pathFinder(nodes, start, dest, comp, cols, 0.001f);

    // Call the algorithm
    auto path = pathFinder.A_star();

    if(m_gameState == State::Running) {
        auto first_tile = m_models[m_gameLevel].first->getObject(pos.x(), pos.y(), ObjectType::Tile); // Tile at the start position
        for(int move : path) {
            first_tile->setData(DataRole::Path, true);
            first_tile = first_tile->getNeighbor(((45 * move + 90) % 360)); // Assign the path tiles to DataRole Path
        }

        for(int move : path) {
            Direction direction = (Direction)((45 * move + 90) % 360);

            // Quick Delay for visualization
            QTime dieTime = QTime::currentTime().addMSecs(100);
            while(QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            // Check whether enemy is on the way of the path and attack it
            QVariant protagonist_direction_variant = m_character->getData(DataRole::Direction);
            Direction protagonist_direction = protagonist_direction_variant.value<Direction>();

            if(auto tile = m_character->getNeighbor(direction)) {
                for(auto child : tile->getAllData()) {
                    if(child[DataRole::Type].toInt() > 99) {
                        while(m_character->getData(DataRole::Energy).toInt() != 100) {
                            QTime dieTime = QTime::currentTime().addMSecs(100);
                            while(QTime::currentTime() < dieTime)
                                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                            if(auto attack = m_character->getBehavior<Attack>()) {
                                attack->attack(direction);
                                emit tick();
                            }
                        }
                    }
                }
            }
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
    auto data = m_models[m_gameLevel].first->getAllData();
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
