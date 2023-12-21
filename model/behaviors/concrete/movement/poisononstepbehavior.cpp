#include "poisononstepbehavior.h"

#include <model/behaviors/poison.h>

bool PoisonOnStepBehavior::getSteppedOn(const QSharedPointer<GameObject> &source) {
    return m_owner->getBehavior<Poison>()->poison(source);
}
