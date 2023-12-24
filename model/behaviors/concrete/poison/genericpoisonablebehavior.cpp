#include "genericpoisonablebehavior.h"
#include "model/behaviors/health.h"

int GenericPoisonableBehavior::getPoisoned(int level) {
    QVariant poisonLevel
      = m_owner->getData(DataRole::PoisonLevel);
    if(poisonLevel.isNull()) {
        throw("Cannot change poison level of object.");
    }

    int newPoison = poisonLevel.toInt() + level;
    if(newPoison > Settings.MAX_POISON) {
        newPoison = Settings.MAX_POISON;
    }

    m_owner->setData(
      DataRole::PoisonLevel, QVariant(newPoison));

    return newPoison;
}

void GenericPoisonableBehavior::poisonEffect() {
    QVariant poisonLevel = m_owner->getData(DataRole::PoisonLevel);
    auto behavior = m_owner->getBehavior<Health>();

    if(poisonLevel.isNull() || behavior.isNull() || poisonLevel.toInt() == 0) {
        return;
    }

    int newPoison = poisonLevel.toInt() - Settings.DAMAGE_PER_TICK;

    if(newPoison > Settings.MIN_POISON) {
        behavior->getHealthChanged(-Settings.DAMAGE_PER_TICK);
    } else {
        m_owner->setData(DataRole::PoisonLevel, 0);
    }
}
