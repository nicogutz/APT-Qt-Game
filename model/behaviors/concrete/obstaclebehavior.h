#ifndef OBSTACLEBEHAVIOR_H
#define OBSTACLEBEHAVIOR_H

#include <model/behaviors/movement.h>

class ObstacleBehavior : public Movement {
public:
    ObstacleBehavior();

    // Movement interface
    bool stepOn(QSharedPointer<GameObject> target) override {
        return false;
    };
    bool getSeppedOn(QSharedPointer<GameObject> source) override {
        return false;
    };
};

#endif // OBSTACLEBEHAVIOR_H
