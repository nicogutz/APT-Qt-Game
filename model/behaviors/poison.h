#ifndef POISON_H
#define POISON_H

#include "behavior.h"

#include "model/gameobject.h"

#include <QSharedPointer>

class Poison : public Behavior {
public:
    virtual ~Poison() = 0;
    Poison& operator=(const Poison&) {
        return *this;
    };

    virtual int poison(QSharedPointer<GameObject> target) = 0;
    virtual int getPoisoned(int level) = 0;
};

#endif // POISON_H
