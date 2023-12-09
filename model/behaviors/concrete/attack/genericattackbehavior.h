#ifndef GENERICATTACKBEHAVIOR_H
#define GENERICATTACKBEHAVIOR_H

#include <model/behaviors/attack.h>

class GenericAttackBehavior : public Attack {
public:
    GenericAttackBehavior(QSharedPointer<GameObject> owner)
        : Attack(owner) {};
    // Attack interface

    int attack(const QSharedPointer<GameObject> &target) override;
    int attack(GameObject::Direction direction) override;
    int attack() override;

    int getAttacked(
      const QSharedPointer<GameObject> &by, int strength) override;
};

#endif // GENERICATTACKBEHAVIOR_H
