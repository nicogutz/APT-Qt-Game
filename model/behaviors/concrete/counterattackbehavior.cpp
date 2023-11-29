#include "counterattackbehavior.h"

int CounterAttackBehavior::getAttacked(const QSharedPointer<GameObject>& target, int strength) {
    GenericAttackBehavior::attack(target);
    return GenericAttackBehavior::getAttacked(target, strength);
}
