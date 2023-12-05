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
    /**
     * @brief stepOn
     * @param target
     * @return
     */
    virtual bool stepOn(const QSharedPointer<GameObject> target) {
        return 0;
    };
    /**
     * @brief stepOn
     * @param direction
     * @return
     */
    virtual bool stepOn(GameObject::Direction direction) {
        return 0;
    };
    /**
     * @brief isStepable
     * @return
     */
    virtual bool isSteppable() {
        return false;
    };
    /**
     * @brief getSeppedOn
     * @param source
     * @return
     */
    virtual bool
    getSeppedOn(const QSharedPointer<GameObject>& source) {
        return 0;
    };
};

#endif // MOVEMENT_H
