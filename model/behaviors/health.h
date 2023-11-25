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

    virtual int heal(QSharedPointer<GameObject> target, int amount) = 0;
    virtual int getHealed(int amount) = 0;
};

#endif // HEALTH_H
