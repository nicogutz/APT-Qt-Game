#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <QSharedPointer>
class GameObject;

class Behavior {
public:
    Behavior(QSharedPointer<GameObject> owner)
        : m_owner(owner) {};

    virtual ~Behavior() = 0;
    Behavior &operator=(const Behavior &) {
        return *this;
    };

protected:
    QSharedPointer<GameObject> m_owner;
};
#endif // BEHAVIOR_H
