#ifndef GENERICMOVABLEBEHAVIOR_H
#define GENERICMOVABLEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericMoveBehavior : public Movement {
private:
    QSharedPointer<GameObject> m_owner;

    // Movement interface
public:
    GenericMoveBehavior(QSharedPointer<GameObject> owner);
    bool stepOn(QSharedPointer<GameObject> target) override;
    bool stepOn(GameObject::Direction direction) override;
};

#endif // GENERICMOVABLEBEHAVIOR_H
