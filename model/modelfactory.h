#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "gameobjectmodel.h"
#include <world.h>
#include <memory>
#include <iostream>
#include "model/behaviors/concrete/movement/poisononstepbehavior.h"
#include "model/behaviors/concrete/movement/genericmovebehavior.h"
#include "model/behaviors/behaviors.h"
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>
#include <pathfinder_class.h>
#include "node.h"

class ObjectModelFactory
{
public:
    ObjectModelFactory();
    GameObjectModel* createModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio);
    std::vector<int> pathFinder();

    QPointer<GameObject> getPro(){return pro;} //temporary
private:
    World m_world;
    std::vector<Node> nodes;
    QPointer<GameObject> pro;
};

#endif // MODELFACTORY_H
