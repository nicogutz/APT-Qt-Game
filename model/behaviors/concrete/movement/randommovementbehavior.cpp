#include "randommovementbehavior.h"

#include <QRandomGenerator>

void RandomMovementBehavior::moveRandomly() {
    bool steppable = true;
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
    }
    if(!steppable) {
        return;
    }

    int direction;
    do {
        direction = QRandomGenerator::global()->bounded(0, 7) * 45;
    } while(!GenericMoveBehavior::stepOn(static_cast<Direction>(direction)));
}
