#include "genericpoisoningbehavior.h"

int GenericPoisoningBehavior::poison(const QSharedPointer<GameObject> &target) {
    auto behaviors = target->getAllBehaviors<Poison>();
    int poisonAmount = 0;

    for(auto behavior : behaviors) {
        if(!behavior.isNull()) {
            int currentLevel = m_owner->getData(GameObject::DataRole::PoisonLevel).toInt();
            int poisonedAmount = behavior->getPoisoned(currentLevel);

            poisonAmount += poisonedAmount;

            m_owner->setData(
              GameObject::DataRole::PoisonLevel,
              QVariant(currentLevel - poisonedAmount));
        }
    }
    return poisonAmount;
}


