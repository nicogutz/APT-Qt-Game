#include "counterattackbehavior.h"

int CounterAttackBehavior::getAttacked(const QPointer<GameObject> &target, int strength) {
    GenericAttackBehavior::attack(target);
    return GenericAttackBehavior::getAttacked(target, strength);
}
