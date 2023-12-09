#include "genericmovebehavior.h"

#include <model/leafobject.h>
#include <model/nodeobject.h>

bool GenericMoveBehavior::stepOn(QSharedPointer<GameObject> target) {
    auto behaviors = target->getAllBehaviors<Movement>();
    bool steppable = true;
    for(auto bh : behaviors) {
        if(bh.isNull())
            return false;

        steppable = steppable && bh->isSteppable();
    }
    if(!steppable)
        return false;

    for(auto bh : behaviors) {
        bh->getSeppedOn(m_owner);
    }
    auto owner = qSharedPointerDynamicCast<LeafObject>(m_owner);

    auto owner_type = static_cast<GameObject::ObjectType>(
      m_owner->getData(GameObject::DataRole::Type).toInt());

    qSharedPointerDynamicCast<NodeObject>(owner->getParent())
      ->popChild(owner_type);
    owner->setParent(target);

    return steppable;
}

bool GenericMoveBehavior::stepOn(GameObject::Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);

    m_owner->setData(
      GameObject::DataRole::Orientation,
      QVariant(static_cast<int>(direction)));

    if(neighbor.isNull()) {
        return false;
    }
    return stepOn(neighbor);
}
