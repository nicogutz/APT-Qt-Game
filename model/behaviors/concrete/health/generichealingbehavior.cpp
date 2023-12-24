#include "generichealingbehavior.h"

int GenericHealingBehavior::heal(const QPointer<GameObject> &target) {
    int availableHealing
      = m_owner->getData(DataRole::Health).toInt();

    auto h_behavior = target->getBehavior<Health>();

    int healAmount = (h_behavior == nullptr) ? 0 : h_behavior->getHealthChanged(availableHealing);

    m_owner->setData(DataRole::Health, availableHealing - healAmount);

    if(healAmount == availableHealing) {
        // TODO: Disappear
        m_owner->setData(DataRole::Visibility, 0);
    }
    return healAmount;
}
