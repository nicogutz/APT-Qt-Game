#include "genericattackbehavior.h"
#include <QRandomGenerator>
#include <model/behaviors/health.h>

int GenericAttackBehavior::attack(const QSharedPointer<GameObject>& target) {
    // Get the strength of the object and calculate the attack strength randomly.
    int strenght = m_owner->getData(GameObject::Strength).toInt();
    int attackStrength = QRandomGenerator::global()->bounded(strenght);

    int count = 0;
    for (auto bh : target->getAllBehaviors<Attack>()) {
        if (!bh.isNull()) {
            count += bh->getAttacked(m_owner, attackStrength);
        }
    };
    return count;
}

int GenericAttackBehavior::attack(GameObject::Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);
    if (neighbor.isNull()) {
        return 0;
    }
    return attack(neighbor);
}

int GenericAttackBehavior::getAttacked(const QSharedPointer<GameObject>& by, int strength) {
    auto behavior = m_owner->getBehavior<Health>();
    return behavior.isNull() ? 0 : behavior->getHealthChanged(-strength);
}
