#include "gameobjectsettings.h"
#include "modelfactory.h"

ObjectModelFactory::ObjectModelFactory()

    : m_nodes()
    , m_protagonist() {
}

GameObjectModel *ObjectModelFactory::createModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, int level) {
    m_nodes.clear();
    World m_world;
    m_world.createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);
    int rows = m_world.getRows(), cols = m_world.getCols();

    QList<QList<QPointer<GameObject>>> worldGrid(rows); // instantiate gameObjectModel aka the worldgrid
    for(int i = 0; i < rows; ++i) {
        worldGrid[i] = QList<QPointer<GameObject>>(cols);
    }

    // insert tiles into model
    auto tiles = m_world.getTiles();
    int i = 0;
    int j = 0;
    for(const auto &tile : tiles) {
        m_nodes.emplace_back(tile->getXPos(), tile->getYPos(), tile->getValue());
        auto *obj = new GameObject({
          {DataRole::Energy, tile->getValue()},
          {DataRole::Position, QPoint(j, i)},
        });
        GameObjectSettings::getFunction(ObjectType::Tile)(obj);
        worldGrid[j][i] = obj;
        if(j == cols - 1) {
            j = 0;
            i++;
        } else {
            j++;
        }
    }
    // Process doorways
    if(level != 1){
        auto *entryDoor = new GameObject({
                                          {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Down)},
                                          });
        GameObjectSettings::getFunction(ObjectType::Doorway)(entryDoor);
        entryDoor->setParent(worldGrid[0][0]);

    }

    auto *exitDoor = new GameObject({
                {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Up)},
                                  });
    GameObjectSettings::getFunction(ObjectType::Doorway)(exitDoor);
    exitDoor->setParent(worldGrid[rows - 1][cols - 1]);

    // Process protagonist
    auto protagonist = m_world.getProtagonist();
    auto *proObj = new GameObject();
    GameObjectSettings::getFunction(ObjectType::Protagonist)(proObj);
    proObj->setParent(worldGrid[protagonist->getXPos()][protagonist->getYPos()]);

    m_protagonist = proObj;

    // Process Health Packs
    auto healthPacks = m_world.getHealthPacks();
    for(const auto &hp : healthPacks) {
        auto *hpObj = new GameObject();
        GameObjectSettings::getFunction(ObjectType::HealthPack)(hpObj);
        hpObj->setParent(worldGrid[hp->getXPos()][hp->getYPos()]);
    }

    // Process Enemies and Poison Enemies
    auto enemies = m_world.getEnemies();
    for(const auto &enemy : enemies) {
        int enemyX = enemy->getXPos();
        int enemyY = enemy->getYPos();
        Node &enemyNode = m_nodes[enemyY * cols + enemyX];
        enemyNode.setValue(1.0);

        ObjectType type = dynamic_cast<PEnemy *>(enemy.get()) ? ObjectType::PoisonEnemy : ObjectType::Enemy;
        auto *enemyObj = new GameObject();
        GameObjectSettings::getFunction(type)(enemyObj);
        enemyObj->setParent(worldGrid[enemyX][enemyY]);
    }

    auto *model = new GameObjectModel(worldGrid);
    return model;
}

std::vector<int> ObjectModelFactory::pathFinder() {
    Comparator<Node> comp = [](const Node &a, const Node &b) {
        return a.h > b.h;
    };

    PathFinder<Node, Tile> pathFinder(m_nodes, &m_nodes.front(), &m_nodes.back(), comp, 30, 0.001f);
    auto path = pathFinder.A_star();

    for(auto p : path) {
        qDebug() << "Move: " << p;
    }
    return path;
}
