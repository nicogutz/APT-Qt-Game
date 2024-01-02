#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "gameobjectmodel.h"
#include <world.h>
#include <memory>
#include <iostream>
#include <QRandomGenerator>
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>
#include <model/noise/perlinnoise.h>
#include <pathfinder_class.h>
#include "node.h"

class ObjectModelFactory {
public:
    ObjectModelFactory();
    GameObjectModel *createModel(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks,
                                 float pRatio, int level, int rows = 40, int columns = 40);
    std::vector<int> pathFinder(int rows);

    QPointer<GameObject> getPro() {
        return m_protagonist;
    } // temporary

    static void createWorld(int level, int width, int height, double difficulty = 1.0);

private:
    World m_world;
    std::vector<Node> m_nodes;
    QPointer<GameObject> m_protagonist;
};

#endif // MODELFACTORY_H
