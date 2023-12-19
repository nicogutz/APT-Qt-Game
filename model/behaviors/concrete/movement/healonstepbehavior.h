#ifndef HEALONSTEPBEHAVIOR_H
#define HEALONSTEPBEHAVIOR_H

#include "genericwalkablebehavior.h"

class HealOnStepBehavior : public GenericWalkableBehavior {
public:
    HealOnStepBehavior(QSharedPointer<GameObject> owner)
        : GenericWalkableBehavior(owner) {};

    // Movement interface
public:
    bool getSteppedOn(const QSharedPointer<GameObject> &source) override;
};

#endif // HEALONSTEPBEHAVIOR_H
