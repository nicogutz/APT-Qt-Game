#include "gameobjectsettings.h"
#include "modelfactory.h"
#include "worldimagefactory.h"

#include <QFile>
#include <QRandomGenerator>

ObjectModelFactory::ObjectModelFactory()

    : m_nodes()
    , m_protagonist() {
}

GameObjectModel *ObjectModelFactory::createModel(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks,
                                                 float pRatio, int level, int rows, int columns) {
    m_nodes.clear();
    World m_world;
    WorldImageFactory::createWorld(level, rows, columns);
    m_world.createWorld(QStringLiteral("./world_%1.png").arg(level), nrOfEnemies, nrOfHealthpacks, pRatio);
    QFile::remove(QStringLiteral("./world_%1.png").arg(level));

    QList<QList<QPointer<GameObject>>> worldGrid(rows); // instantiate gameObjectModel aka the worldgrid
    for(int i = 0; i < rows; ++i) {
        worldGrid[i] = QList<QPointer<GameObject>>(columns);
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
        if(j == columns - 1) {
            j = 0;
            i++;
        } else {
            j++;
        }
    }
    // Process doorways
    if(level) {
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
    exitDoor->setParent(worldGrid[rows - 1][columns - 1]);

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
    int enemyLocations[rows][columns];
    memset(enemyLocations, 0, sizeof(enemyLocations));

    for(const auto &enemy : enemies) {
        int enemyX = enemy->getXPos();
        int enemyY = enemy->getYPos();
        enemyLocations[enemyX - 1][enemyY - 1] = 1;
        if((enemyX == columns - 1 && enemyY == rows - 1) || (enemyX == 0 && enemyY == 0)) {
            enemyX = columns - 2;
            enemyY = rows - 2; // make sure no enemies on the doorway
        }
        Node &enemyNode = m_nodes[enemyY * columns + enemyX];
        // enemyNode.setValue(1.0);

        ObjectType type = dynamic_cast<PEnemy *>(enemy.get()) ? ObjectType::PoisonEnemy : ObjectType::Enemy;
        auto *enemyObj = new GameObject();
        GameObjectSettings::getFunction(type)(enemyObj);
        enemyObj->setParent(worldGrid[enemyX][enemyY]);
    }

    // Moving enemies not placed in the same place as other enemies.
    int movingEnemies = 5;
    while(movingEnemies) {
        auto *enemyObj = new GameObject();
        GameObjectSettings::getFunction(ObjectType::MovingEnemy)(enemyObj);
        int x = 0, y = 0;
        do {
            x = QRandomGenerator::global()->bounded(1, rows - 2);
            y = QRandomGenerator::global()->bounded(1, columns - 2);
        } while(!enemyLocations[x][y]);
        enemyObj->setParent(worldGrid[x][y]);
        movingEnemies--;
    }

    auto *model = new GameObjectModel(worldGrid);

    return model;
}

std::vector<int> ObjectModelFactory::pathFinder(int rows) {
    Comparator<Node> comp = [](const Node &a, const Node &b) {
        return a.h > b.h;
    };

    PathFinder<Node, Tile> pathFinder(m_nodes, &m_nodes.front(), &m_nodes.back(), comp, rows, 0.001f);
    auto path = pathFinder.A_star();

    for(auto p : path) {
        qDebug() << "Move: " << p;
    }
    return path;
}
