#ifndef GENERICMOVEBEHAVIOR_H
#define GENERICMOVEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericMoveBehavior : public Movement {
public:
    GenericMoveBehavior(QSharedPointer<GameObject> owner)
        : Movement(owner) {};
    bool stepOn(QSharedPointer<GameObject> target) override;
    bool stepOn(Direction direction) override;
};

#endif // GENERICMOVEBEHAVIOR_H
