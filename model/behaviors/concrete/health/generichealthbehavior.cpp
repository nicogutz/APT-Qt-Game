#include "generichealthbehavior.h"

int GenericHealthBehavior::getHealthChanged(int amount) {
    QVariant currentHealth
      = m_owner->getData(DataRole::Health);
    if(currentHealth.isNull()) {
        throw("Cannot change health of object without health");
    }

    int newHealth = currentHealth.toInt() + amount;

    if(newHealth <= 0) {
        die();
    } else if(newHealth > Settings.MAX_HEALTH) {
        newHealth = Settings.MAX_HEALTH;
    }

    m_owner->setData(
      DataRole::Health, QVariant(newHealth));

    return newHealth;
}

void GenericHealthBehavior::die() {
    emit objectKilled(m_owner);
}
