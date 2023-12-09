#ifndef POISONONSTEPBEHAVIOR_H
#define POISONONSTEPBEHAVIOR_H

#include "genericwalkablebehavior.h"

class PoisonOnStepBehavior : public GenericWalkableBehavior {
public:
    PoisonOnStepBehavior(QSharedPointer<GameObject> owner)
        : GenericWalkableBehavior(owner) {};

    // Movement interface
public:
    bool getSeppedOn(const QSharedPointer<GameObject> &source) override;
};

#endif // POISONONSTEPBEHAVIOR_H
