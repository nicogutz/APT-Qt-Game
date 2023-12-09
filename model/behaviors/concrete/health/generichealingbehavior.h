#ifndef GENERICHEALINGBEHAVIOR_H
#define GENERICHEALINGBEHAVIOR_H

#include <model/behaviors/health.h>
#include <model/behaviors/movement.h>

class GenericHealingBehavior : public Health {
public:
    GenericHealingBehavior(QSharedPointer<GameObject> owner)
        : Health(owner) {};

    // Health interface
public:
    int heal(const QSharedPointer<GameObject> &target) override;
};

#endif // GENERICHEALINGBEHAVIOR_H
