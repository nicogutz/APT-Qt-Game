#ifndef POISONONKILLEDBEHAVIOR_H
#define POISONONKILLEDBEHAVIOR_H

#include "generichealthbehavior.h"

class PoisonOnKilledBehavior : public GenericHealthBehavior {
public:
    PoisonOnKilledBehavior(QSharedPointer<GameObject> owner)
        : GenericHealthBehavior(owner) {};

    // Health interface
    void die() override;

public slots:
    void extracted();
    void spreadPoison();

private:
    unsigned int m_ticksToPoison, m_poisonCount = 0;
    unsigned long m_tickCount = 0;
};

#endif // POISONONKILLEDBEHAVIOR_H
