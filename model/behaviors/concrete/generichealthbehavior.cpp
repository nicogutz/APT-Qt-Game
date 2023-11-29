#include "generichealthbehavior.h"

int GenericHealthBehavior::heal(const QSharedPointer<GameObject>& target) {
    return 0;
}

int GenericHealthBehavior::getHealthChanged(int amount) {
    QVariant currentHealth = m_owner->getData(GameObject::DataRole::Health);
    if (currentHealth.isNull()) {
        throw("Cannot change health of object without health");
    }

    int new_health = currentHealth.toInt() + amount;

    if (new_health < 0) {
        emit objectKilled(m_owner);
    } else if (new_health > Settings.MAX_HEALTH) {
        new_health = Settings.MAX_HEALTH;
    }

    m_owner->setData(GameObject::DataRole::Health, QVariant(new_health));

    return new_health;
}
