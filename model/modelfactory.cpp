#include "modelfactory.h"

ObjectModelFactory::ObjectModelFactory(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio)
    :world (World())
{

    world.createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);


}



QList<QList<QPointer<GameObject>>> ObjectModelFactory::createModel() {

    int rows = world.getRows(), cols = world.getCols();

    QList<QList<QPointer<GameObject>>> worldGrid(rows); // instantiate gameObjectModel aka the worldgrid
    QMap<DataRole, QVariant> tileData({{DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Tile)}});
    for(int i = 0; i < rows; ++i) {
        worldGrid[i] = QList<QPointer<GameObject>>(cols);
    }

    // insert tiles into model
    auto tiles = world.getTiles();
    int i = 0;
    int j = 0;
    for (const auto& tile : tiles) {
        auto *obj = new GameObject(tileData);
        obj->setData(DataRole::Energy, tile->getValue());
        obj->setData(DataRole::Position, QPoint(i, j));
        obj->setBehavior<Movement>(QSharedPointer<PoisonOnStepBehavior>::create(obj));
        obj->setBehavior<Poison>(QSharedPointer<GenericPoisoningBehavior>::create(obj));
        worldGrid[i][j] = obj;
        if (j==cols-1){
            j=0;
            i++;
        }else{
            j++;
        }
    }

    return worldGrid;
}

/*
void ObjectModelFactory::pathFinder()
{

    // Convert World Tiles to Nodes
    std::vector<Node> nodes;
    for (const auto& tilePtr : world.getTiles()) {
        nodes.emplace_back(tilePtr->getXPos(), tilePtr->getYPos(), tilePtr->getValue());
    }
    Comparator<Node> comp = [](const Node& a, const Node& b) {
        return a.h > b.h;
    };


    std::unique_ptr<Tile> startTile = world.getTiles().front();
    std::unique_ptr<Tile> destinationTile = world.getTiles().back();

    int cols = world.getCols();
    PathFinder<Node, Tile> pathFinder(nodes, startTile, destinationTile, comp, world.getCols(), 1.0f);

    // Find the path
    auto path = pathFinder.A_star();

    // Output the path for debugging purposes
    for (auto p : path) {
        qDebug() << "Move: " << p;
    }

}

*/

