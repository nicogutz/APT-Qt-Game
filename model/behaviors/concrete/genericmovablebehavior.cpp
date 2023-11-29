#include "genericmovablebehavior.h"

#include <model/leafobject.h>
#include <model/nodeobject.h>

bool GenericMoveBehavior::stepOn(const QSharedPointer<GameObject>& target) {
    auto behaviors = target->getAllBehaviors<Movement>();
    bool steppable = true;
    for (auto bh : behaviors) {
        if (bh.isNull()) {
            return false;
        }
        steppable = steppable && bh->isSteppable();
    }
    auto owner = qSharedPointerDynamicCast<LeafObject>(m_owner);
    auto owner_type = (GameObject::ObjectType)m_owner->getData(GameObject::Type).toInt();
    qSharedPointerDynamicCast<NodeObject>(owner->getParent())->popChild(owner_type);
    owner->setParent(target);
    return steppable;
}

bool GenericMoveBehavior::stepOn(GameObject::Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);
    if (neighbor.isNull()) {
        return false;
    }
    return stepOn(neighbor);
}

bool GenericMoveBehavior::isSteppable() {
}

bool GenericMoveBehavior::getSeppedOn(const QSharedPointer<GameObject>& source) {
}
