#ifndef GENERICATTACKBEHAVIOR_H
#define GENERICATTACKBEHAVIOR_H

#include <model/behaviors/attack.h>

class GenericAttackBehavior : public Attack {
public:
    GenericAttackBehavior(QSharedPointer<GameObject> owner)
        : m_owner(owner) {};
    // Attack interface

    int attack(const QSharedPointer<GameObject>& target) override;
    int attack(GameObject::Direction direction) override;
    int getAttacked(const QSharedPointer<GameObject>& by, int strength) override;

protected:
    QSharedPointer<GameObject> m_owner;
};

#endif // GENERICATTACKBEHAVIOR_H
