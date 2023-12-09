#include "poisononkilledbehavior.h"

#include <qtimer.h>

void PoisonOnKilledBehavior::die() {
    //    m_owner->getBehavior()

    GenericHealthBehavior::die();
}
