#include "poisononkilledbehavior.h"
#include "model/behaviors/poison.h"

#include <QRandomGenerator>

void PoisonOnKilledBehavior::die() {
    //    m_owner->getBehavior()
    m_poisonCount = Poison::SETTINGS::POISON_SPREAD_TIMES;

    m_ticksToPoison = QRandomGenerator::global()->bounded(0, Poison::SETTINGS::POISON_SPREAD_MAX_TICKS);

    GenericHealthBehavior::die();
}

void PoisonOnKilledBehavior::spreadPoison() {
    if(m_poisonCount) {
        m_tickCount++;

        if(m_ticksToPoison < m_tickCount) {
            return;
        }

        m_ticksToPoison = QRandomGenerator::global()->bounded(0, Poison::SETTINGS::POISON_SPREAD_MAX_TICKS);
        m_tickCount = 0;

        for(const auto &n : m_owner->getAllNeighbors(Poison::SETTINGS::POISON_SPREAD_TIMES - m_poisonCount)) {
            m_owner->getBehavior<Poison>()->poison(n);
        }

        m_poisonCount--;
    }
}
