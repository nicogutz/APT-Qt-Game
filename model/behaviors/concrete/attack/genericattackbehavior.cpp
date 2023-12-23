#include <QRandomGenerator>
#include "genericattackbehavior.h"
#include "model/behaviors/health.h"
#include "publicenums.h"

int GenericAttackBehavior::attack(const QSharedPointer<GameObject> &target) {
    // Get the strength of the object and calculate the attack
    // strength randomly.
    int strenght = m_owner->getData(DataRole::Strength).toInt();
    int attackStrength = QRandomGenerator::global()->bounded(strenght);

    int count = 0;
    // TODO: Add emit signal to animate attack.
    for(auto bh : target->getAllBehaviors<Attack>()) {
        auto at = qSharedPointerDynamicCast<Attack>(bh);
        if(!bh.isNull()) {
            count += at->getAttacked(m_owner, attackStrength);
        }
    };
    return count;
}

int GenericAttackBehavior::attack(Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);
    if(neighbor.isNull()) {
        return 0;
    }
    return attack(neighbor);
}
int GenericAttackBehavior::attack() {
    return attack(static_cast<Direction>(
      m_owner->getData(DataRole::Direction).toInt()));
}

int GenericAttackBehavior::getAttacked(const QSharedPointer<GameObject> &by,
                                       int strength) {
    auto behavior = m_owner->getBehavior<Health>();
    return behavior.isNull() ? 0 : behavior->getHealthChanged(-strength);
}
