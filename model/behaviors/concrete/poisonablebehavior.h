#ifndef POISONABLEBEHAVIOR_H
#define POISONABLEBEHAVIOR_H

#include <model/behaviors/poison.h>

class PoisonableBehavior : public Poison {
public:
    PoisonableBehavior();

    // Poison interface
public:
    int getPoisoned(int level) override;
};

#endif // POISONABLEBEHAVIOR_H
