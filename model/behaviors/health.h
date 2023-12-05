#ifndef HEALTH_H
#define HEALTH_H

#include "behavior.h"

#include "model/gameobject.h"
#include <QSharedPointer>

class Health : public Behavior {
public:
    virtual ~Health() = 0;
    Health& operator=(const Health&) {
        return *this;
    };
    const struct SETTINGS {
        const int MAX_HEALTH = 100;
        const int MIN_HEALTH = 0;
        const int HEALTH_PACK_HEALING = 10;
    } Settings;

    /**
     * @brief heal
     * @param target
     * @return
     */
    virtual int heal(const QSharedPointer<GameObject>& target) = 0;
    /**
     * @brief getHealthChange
     * @param amount
     * @return
     */
    virtual int getHealthChanged(int amount) = 0;
};

#endif // HEALTH_H
