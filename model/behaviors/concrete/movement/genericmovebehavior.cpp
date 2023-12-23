#include "genericmovebehavior.h"

#include <model/leafobject.h>
#include <model/nodeobject.h>

bool GenericMoveBehavior::stepOn(QSharedPointer<GameObject> target) {
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
    auto owner = qSharedPointerDynamicCast<LeafObject>(m_owner);

    auto owner_type = static_cast<ObjectType>(m_owner->getData(DataRole::Type).toInt());

    qSharedPointerDynamicCast<NodeObject>(owner->getParent())->popChild(owner_type);
    owner->setParent(target);

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
