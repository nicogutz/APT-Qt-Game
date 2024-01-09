#include "poisononstepbehavior.h"

#include <model/behaviors/poison.h>

bool PoisonOnStepBehavior::getSteppedOn(const QPointer<GameObject> &source) {
    m_owner->getBehavior<Poison>()->poison(source);
    return GenericWalkableBehavior::getSteppedOn(source);
}
