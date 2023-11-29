#ifndef GENERICMOVABLEBEHAVIOR_H
#define GENERICMOVABLEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericMoveBehavior : public Movement {
public:
    GenericMoveBehavior(QSharedPointer<GameObject> owner);
    ;

private:
    QSharedPointer<GameObject> m_owner;

    // Movement interface
public:
    bool stepOn(QSharedPointer<GameObject> target) override;
    bool stepOn(GameObject::Direction direction) override;
    bool getSeppedOn(const QSharedPointer<GameObject>& source) override;
    bool isSteppable() override;
};

#endif // GENERICMOVABLEBEHAVIOR_H
