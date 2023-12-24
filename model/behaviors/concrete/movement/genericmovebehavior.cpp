#include "genericmovebehavior.h"

bool GenericMoveBehavior::stepOn(QPointer<GameObject> target) {
    auto behaviors = target->getAllBehaviors<Movement>();
    bool steppable = true;
    for(const auto &bh : behaviors) {
        if(bh.isNull())
            return false;

        steppable = steppable && bh->isSteppable();
    }
    if(!steppable)
        return false;

    for(const auto &bh : behaviors) {
        bh->getSteppedOn(m_owner);
    }

    m_owner->setParent(target);
    return steppable;
}

bool GenericMoveBehavior::stepOn(Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);

    m_owner->setData(DataRole::Direction, QVariant(static_cast<int>(direction)));

    if(neighbor.isNull()) {
        return false;
    }
    return stepOn(neighbor);
}
