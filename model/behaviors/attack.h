#ifndef ATTACK_H
#define ATTACK_H

#include <QSharedPointer>

#include <model/gameobject.h>

class Attack : public Behavior {
public:
    virtual ~Attack() = 0;
    Attack& operator=(const Attack&) {
        return *this;
    };
    /**
     * @brief attack
     * @param target
     * @return
     */
    virtual int attack(const QSharedPointer<GameObject>& target) = 0;
    /**
     * @brief attack
     * @param target
     * @return
     */
    virtual int attack(GameObject::Direction direction) = 0;
    /**
     * @brief getAttacked
     * @param strength
     * @return
     */
    virtual int getAttacked(const QSharedPointer<GameObject>& by, int strength) = 0;
};

#endif // ATTACK_H
