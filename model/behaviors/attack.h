#ifndef ATTACK_H
#define ATTACK_H

#include <QSharedPointer>

#include <model/gameobject.h>

class Attack {
public:
    virtual ~Attack() = 0;
    Attack& operator=(const Attack&) {
        return *this;
    };

    virtual int attack(QSharedPointer<GameObject> target, int strength) = 0;
    virtual int getAttacked(QSharedPointer<GameObject> source, int strength) = 0;
};

#endif // ATTACK_H
