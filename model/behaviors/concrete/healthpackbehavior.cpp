#include "healthpackbehavior.h"

int HealthPackBehavior::heal(
    const QSharedPointer<GameObject>& target) {
    int availableHealing
        = m_owner->getData(GameObject::DataRole::Health).toInt();

    auto h_behavior = target->getBehavior<Health>();

    int healAmount = (h_behavior == nullptr)
        ? 0
        : h_behavior->getHealthChanged(availableHealing);

    m_owner->setData(
        GameObject::DataRole::Health, availableHealing - healAmount);

    if (healAmount == availableHealing) {
        // TODO: Disappear
        m_owner->setData(GameObject::DataRole::Visibility, 0);
    }
    return healAmount;
}
