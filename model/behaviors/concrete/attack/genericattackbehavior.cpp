#include <QRandomGenerator>
#include "genericattackbehavior.h"
#include "model/behaviors/health.h"
#include "model/behaviors/movement.h"
#include "publicenums.h"

int GenericAttackBehavior::attack(const QPointer<GameObject> &target) {
    // Get the strength of the object and calculate the attack
    // strength randomly.
    int strenght = m_owner->getData(DataRole::Strength).toInt();
    int attackStrength = QRandomGenerator::global()->bounded(1, strenght);

    int attacks = 0;
    for(auto bh : target->getAllBehaviors<Attack>()) {
        auto at = qSharedPointerDynamicCast<Attack>(bh);
        if(!bh.isNull()) {
            int healthChange = at->getAttacked(m_owner, attackStrength);
            if(healthChange + attackStrength > 0) {
                m_owner->setData(DataRole::Energy, Movement::SETTINGS::MAX_ENERGY);
            }
            attacks += healthChange;
        }
    };
    return -attacks;
}

int GenericAttackBehavior::attack(Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);
    if(!neighbor) {
        return 0;
    }
    return attack(neighbor);
}
int GenericAttackBehavior::attack() {
    return attack(m_owner->getData(DataRole::Direction).value<Direction>());
}

int GenericAttackBehavior::getAttacked(const QPointer<GameObject> &by, int strength) {
    auto behavior = m_owner->getBehavior<Health>();
    return behavior.isNull() ? 0 : behavior->getHealthChanged(-strength);
}
