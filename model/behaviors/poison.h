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
    /**
     * @brief poison
     * @param target
     * @return
     */
    virtual int poison(const QSharedPointer<GameObject>& target) {
        return 0;
    };
    /**
     * @brief getPoisoned
     * @param level
     * @return
     */
    virtual int getPoisoned(int level) = 0;
};

#endif // POISON_H
