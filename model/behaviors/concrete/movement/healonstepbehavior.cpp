#include "healonstepbehavior.h"

#include <model/behaviors/health.h>

bool HealOnStepBehavior::getSeppedOn(const QSharedPointer<GameObject> &source) {
    return m_owner->getBehavior<Health>()->heal(source);
}
