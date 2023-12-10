#include "genericpoisoningbehavior.h"

int GenericPoisoningBehavior::poison(const QSharedPointer<GameObject> &target) {
    auto behaviors = target->getAllBehaviors<Poison>();
    int poisonAdminisered = 0;

    for(auto &behavior : behaviors) {
        if(!behavior.isNull()) {
            int currentLevel = m_owner->getData(GameObject::DataRole::PoisonLevel).toInt();

            if(currentLevel <= 0)
                continue;

            int poisonedAmount = currentLevel > Poison::SETTINGS::MAX_POISON_PER_ACTION
              ? Poison::SETTINGS::MAX_POISON_PER_ACTION
              : currentLevel;

            poisonAdminisered += poisonedAmount;

            m_owner->setData(
              GameObject::DataRole::PoisonLevel,
              QVariant(currentLevel - poisonedAmount));
        }
    }
    return poisonAdminisered;
}
