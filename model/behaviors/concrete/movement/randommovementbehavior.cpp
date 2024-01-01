#include "randommovementbehavior.h"

#include <QRandomGenerator>

void RandomMovementBehavior::moveRandomly() {
    bool steppable = true;
    float energy = 0;
    for(const auto &neighbor : m_owner->getAllNeighbors()) {
        if(!neighbor) {
            continue;
        }
        steppable &= neighbor->getBehavior<Movement>()->isSteppable();
        for(const auto &data : neighbor->getAllData()) {
            if(data[DataRole::Type].value<ObjectType>() == ObjectType::Protagonist) {
                return;
            }
        }
        float neighborEnergy = neighbor->getData(DataRole::Energy).toFloat();
        neighborEnergy = neighborEnergy == INFINITY ? 1000 : neighborEnergy;
        energy = neighborEnergy > energy ? neighborEnergy : energy;
    }

    if(!steppable || energy > m_owner->getData(DataRole::Energy).toFloat()) {
        m_owner->setData(DataRole::Energy, 0);
        disconnect(m_owner, &GameObject::tick, this, &RandomMovementBehavior::moveRandomly);
        return;
    }

    int direction;
    do {
        direction = QRandomGenerator::global()->bounded(0, 7) * 45;
    } while(!GenericMoveBehavior::stepOn(static_cast<Direction>(direction)));
}
