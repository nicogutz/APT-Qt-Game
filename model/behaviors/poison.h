#ifndef POISON_H
#define POISON_H

#include "behavior.h"

#include "model/gameobject.h"

#include <QSharedPointer>

class Poison : public Behavior {
public:
    Poison(QSharedPointer<GameObject> owner)
        : Behavior(owner) {};

    virtual ~Poison() = 0;
    const struct SETTINGS {
        const int MAX_POISON = 100;
        const int MIN_POISON = 0;
        const int POISON_PER_TICK = 10;
        const int DAMAGE_PER_TICK = 5;
    } Settings;

    Poison &operator=(const Poison &) {
        return *this;
    };
    /**
     * @brief poison
     * @param target
     * @return
     */
    virtual int poison(const QSharedPointer<GameObject> &target) {
        return 0;
    };
    /**
     * @brief getPoisoned
     * @param level
     * @return
     */
    virtual int getPoisoned(int level) {
        return 0;
    };
    /**
     * @brief getPoisoned
     * @param level
     * @return
     */
    virtual int clearPoison(int level) {
        return 0;
    };
};

#endif // POISON_H
