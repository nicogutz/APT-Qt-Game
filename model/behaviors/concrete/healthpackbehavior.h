#ifndef HEALTHPACKBEHAVIOR_H
#define HEALTHPACKBEHAVIOR_H

#include <model/behaviors/health.h>
#include <model/behaviors/movement.h>

class HealthPackBehavior : public Health {
public:
    HealthPackBehavior(QSharedPointer<GameObject> owner);

    // Health interface
public:
    int heal(const QSharedPointer<GameObject>& target) override;

private:
    QSharedPointer<GameObject> m_owner;
};

#endif // HEALTHPACKBEHAVIOR_H
