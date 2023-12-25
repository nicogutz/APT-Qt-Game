#include "modelfactory.h"

ObjectModelFactory::ObjectModelFactory()
{

}



QList<QList<QPointer<GameObject>>> ObjectModelFactory::createModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio) {
    World world;
    world.createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);
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
        std::cout << tile->getValue();
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


