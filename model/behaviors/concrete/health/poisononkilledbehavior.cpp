#include "poisononkilledbehavior.h"
#include "model/behaviors/attack.h"
#include "model/behaviors/poison.h"

#include <QRandomGenerator>

#include <model/behaviors/concrete/movement/genericwalkablebehavior.h>

void PoisonOnKilledBehavior::die() {
    m_count = m_poisonTimes = QRandomGenerator::global()->bounded(
      Poison::SETTINGS::POISON_SPREAD_TIMES_MIN,
      Poison::SETTINGS::POISON_SPREAD_TIMES_MAX);

    m_owner->removeBehavior<Attack>();
    m_owner->setBehavior<Movement>(QSharedPointer<GenericWalkableBehavior>::create(m_owner));

    m_nextPoison = QRandomGenerator::global()->bounded(
      Poison::SETTINGS::POISON_SPREAD_MIN_TICKS,
      Poison::SETTINGS::POISON_SPREAD_MAX_TICKS);

    connect(m_owner, &GameObject::tick, this, &PoisonOnKilledBehavior::spreadPoison);
}

void PoisonOnKilledBehavior::spreadPoison() {
    m_tickCount++;

    if(m_nextPoison > m_tickCount) {
        return;
    }

    if(m_count) {
        m_tickCount = 0;
        m_nextPoison = QRandomGenerator::global()->bounded(
          Poison::SETTINGS::POISON_SPREAD_MIN_TICKS,
          Poison::SETTINGS::POISON_SPREAD_MAX_TICKS);

        for(const auto &n : m_owner->getAllNeighbors(m_poisonTimes - m_count)) {
            if(n) {
                m_owner->getBehavior<Poison>()->poison(n);
            }
        }

        m_count--;
    } else {
        m_owner->setData(DataRole::Destroyed, true);
        delete m_owner;
    }
}
