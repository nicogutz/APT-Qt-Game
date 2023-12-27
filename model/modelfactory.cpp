#include "modelfactory.h"

ObjectModelFactory::ObjectModelFactory()

    : nodes(),
    pro()
{

}

GameObjectModel* ObjectModelFactory::createModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio) {
    World m_world;
    m_world.createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);
    int rows = m_world.getRows(), cols = m_world.getCols();

    QList<QList<QPointer<GameObject>>> worldGrid(rows); // instantiate gameObjectModel aka the worldgrid
    QMap<DataRole, QVariant> tileData({{DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Tile)}});
    for(int i = 0; i < rows; ++i) {
        worldGrid[i] = QList<QPointer<GameObject>>(cols);
    }

    // insert tiles into model
    auto tiles = m_world.getTiles();
    int i = 0;
    int j = 0;
    for(const auto &tile : tiles) {
        nodes.emplace_back(tile->getXPos(), tile->getYPos(), tile->getValue());
        auto *obj = new GameObject(tileData);
        obj->setData(DataRole::Energy, tile->getValue());
        obj->setData(DataRole::Position, QPoint(i, j));
        obj->setBehavior<Movement>(QSharedPointer<PoisonOnStepBehavior>::create(obj));
        obj->setBehavior<Poison>(QSharedPointer<GenericPoisoningBehavior>::create(obj));
        worldGrid[i][j] = obj;
        if(j == cols - 1) {
            j = 0;
            i++;
        } else {
            j++;
        }
    }

    // Process protagonist
    auto protagonist = m_world.getProtagonist();
    auto *proObj = new GameObject(QMap<DataRole, QVariant>({
        {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Protagonist)},
        {DataRole::Health, protagonist->getHealth()},
        {DataRole::Energy, protagonist->getEnergy()},
        {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Right)},
        {DataRole::Position, QPoint(protagonist->getXPos(), protagonist->getYPos())}
    }));
    proObj->setBehavior<Movement>(QSharedPointer<GenericMoveBehavior>::create(proObj));
    proObj->setBehavior<Poison>(QSharedPointer<GenericPoisonableBehavior>::create(proObj));
    proObj->setParent(worldGrid[protagonist->getXPos()][protagonist->getYPos()]);

    pro = proObj;

    // Process Health Packs
    auto healthPacks = m_world.getHealthPacks();
    for(const auto &hp : healthPacks) {
        auto *hpObj = new GameObject(QMap<DataRole, QVariant>({
            {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::HealthPack)},
            {DataRole::Position, QPoint(hp->getXPos(), hp->getYPos())}
        }));
        hpObj->setParent(worldGrid[hp->getXPos()][hp->getYPos()]);
    }

    // Process Enemies and Poison Enemies
    auto enemies = m_world.getEnemies();
    for(const auto &enemy : enemies) {
        ObjectType type = (dynamic_cast<PEnemy*>(enemy.get()) != nullptr) ? ObjectType::PoisonEnemy : ObjectType::Enemy;
        auto *enemyObj = new GameObject(QMap<DataRole, QVariant>({
            {DataRole::Type, QVariant::fromValue<ObjectType>(type)},
            {DataRole::Position, QPoint(enemy->getXPos(), enemy->getYPos())},
            {DataRole::Strength, 0} // TODO: get strength from the library?

        }));
        enemyObj->setParent(worldGrid[enemy->getXPos()][enemy->getYPos()]);
        // TODO: get poison level from the library?

        //        if (type == ObjectType::PoisonEnemy){
        //            enemyObj->setData(DataRole::PoisonLevel, enemy->getPoisonLevel());
        //        }
    }

    auto *model = new GameObjectModel(worldGrid);
    return model;
}

std::vector<int> ObjectModelFactory::pathFinder() {

    Comparator<Node> comp = [](const Node &a, const Node &b) {
        return a.h > b.h;
    };

    PathFinder<Node, Tile> pathFinder(nodes, &nodes.front(), &nodes.back(), comp, m_world.getCols(), 1.0f);
    auto path = pathFinder.A_star();

    for(auto p : path) {
        qDebug() << "Move: " << p;
    }
    return path;
}


