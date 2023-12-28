#include "genericpoisoningbehavior.h"

int GenericPoisoningBehavior::poison(const QPointer<GameObject> &target) {
    auto behaviors = target->getAllBehaviors<Poison>();
    int poisonAdminisered = 0;

    for(const auto &behavior : behaviors) {
        if(behavior) {
            int currentLevel = m_owner->getData(DataRole::PoisonLevel).toInt();

            if(currentLevel <= 0)
                continue;

            int poisonedAmount = currentLevel > Poison::SETTINGS::MAX_POISON_PER_ACTION
              ? Poison::SETTINGS::MAX_POISON_PER_ACTION
              : currentLevel;
            poisonedAmount = behavior->getPoisoned(poisonedAmount);
            poisonAdminisered += poisonedAmount;

            m_owner->setData(
              DataRole::PoisonLevel,
              QVariant(currentLevel - poisonedAmount));
        }
    }
    return poisonAdminisered;
}
