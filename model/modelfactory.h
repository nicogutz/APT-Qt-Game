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

class ObjectModelFactory
{
public:
    ObjectModelFactory();
    QList<QList<QPointer<GameObject>>> createModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio);

};

#endif // MODELFACTORY_H
