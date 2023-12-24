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
    m_owner->event(new QEvent(QEvent::ParentChange));
    return steppable;
}

bool GenericMoveBehavior::stepOn(Direction direction) {
    auto currentDirection = m_owner->getData(DataRole::Direction).value<Direction>();
    if(direction != currentDirection) {
        m_owner->setData(DataRole::Direction, QVariant::fromValue<Direction>(direction));
        return false;
    }

    auto neighbor = m_owner->getNeighbor(direction);
    if(!neighbor) {
        return false;
    }

    return stepOn(neighbor);
}
