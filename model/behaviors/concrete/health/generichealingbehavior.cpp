#include "generichealingbehavior.h"

int GenericHealingBehavior::heal(const QPointer<GameObject> &target) {
    int availableHealing = m_owner->getData(DataRole::Health).toInt();

    auto h_behavior = target->getBehavior<Health>();

    int healAmount = h_behavior ? h_behavior->getHealthChanged(availableHealing) : 0;

    m_owner->setData(DataRole::Health, availableHealing - healAmount);

    if(healAmount >= availableHealing) {
        m_owner->setData(DataRole::Destroyed, true);
        delete m_owner;
    }
    return healAmount;
}
