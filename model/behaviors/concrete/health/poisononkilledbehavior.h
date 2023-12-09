#ifndef POISONONKILLEDBEHAVIOR_H
#define POISONONKILLEDBEHAVIOR_H

#include "generichealthbehavior.h"

class PoisonOnKilledBehavior : public GenericHealthBehavior {
public:
    PoisonOnKilledBehavior(QSharedPointer<GameObject> owner)
        : GenericHealthBehavior(owner) { }

    // Health interface
    void die() override;

public slots:
    void tick(unsigned long int clock);

private:
    int m_poison_rate;
};

#endif // POISONONKILLEDBEHAVIOR_H
