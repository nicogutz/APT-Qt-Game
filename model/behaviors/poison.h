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
    const static struct SETTINGS {
        // Max/Min allowed amount of poison for a Game Object to get during gameplay.
        const static int MAX_POISON = 100;
        const static int MIN_POISON = 0;

        // How much a Game Object will poison per tick/action.
        const static int MAX_POISON_PER_ACTION = 10;
        // How many times a GO will spread its poison.
        const static int POISON_SPREAD_TIMES = 3;
        // The Max ticks between poison spread
        const static int POISON_SPREAD_MAX_TICKS = 5;
        // How much damage poison does per tick.
        const static int DAMAGE_PER_TICK = 5;
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
