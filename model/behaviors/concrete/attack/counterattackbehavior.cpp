#include "counterattackbehavior.h"

int CounterAttackBehavior::getAttacked(const QPointer<GameObject> &target, int strenght) {
    // This is neat, the opposite angle is the angle + 180,
    // modulo 360 makes sure it is always smaller than 360 deg.
    int newDirection = (180 + target->getData(DataRole::Direction).toInt()) % 360;
    m_owner->setData(DataRole::Direction, newDirection);

    GenericAttackBehavior::attack(target);
    return GenericAttackBehavior::getAttacked(target, strenght);
}
