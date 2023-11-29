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
    virtual bool stepOn(const QSharedPointer<GameObject> target) = 0;
    /**
     * @brief stepOn
     * @param direction
     * @return
     */
    virtual bool stepOn(GameObject::Direction direction) = 0;
    /**
     * @brief isStepable
     * @return
     */
    virtual bool isSteppable() = 0;
    /**
     * @brief getSeppedOn
     * @param source
     * @return
     */
    virtual bool getSeppedOn(const QSharedPointer<GameObject>& source) = 0;
};

#endif // MOVEMENT_H
