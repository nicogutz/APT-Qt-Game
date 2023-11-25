#ifndef FIRE_H
#define FIRE_H

#include "behavior.h"

#include <QSharedPointer>
#include <model/gameobject.h>

class Fire : public Behavior {
public:
    virtual ~Fire() = 0;
    Fire& operator=(const Fire&) {
        return *this;
    };

    virtual int setOnFire(QSharedPointer<GameObject> target) = 0;
    virtual int extinguish(QSharedPointer<GameObject> target) = 0;

    virtual int getSetOnFire() = 0;
    virtual int getExtinguished() = 0;
};

#endif // FIRE_H
