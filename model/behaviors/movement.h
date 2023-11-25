#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "behavior.h"

#include <model/gameobject.h>

#include <QSharedPointer>

class Movement : public Behavior {
public:
    virtual ~Movement() = 0;
    Movement& operator=(const Movement&) {
        return *this;
    };

    virtual bool stepOn(QSharedPointer<GameObject> target) = 0;
    virtual bool getSeppedOn(QSharedPointer<GameObject> source) = 0;
};

#endif // MOVEMENT_H
