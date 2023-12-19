#ifndef LEAFOBJECT_H
#define LEAFOBJECT_H

#include "gameobject.h"

class LeafObject : public GameObject {
public:
    LeafObject()
        : GameObject() {
    }
    // Parent getters and setters
    QSharedPointer<GameObject> &getParent() const;
    bool setParent(const QSharedPointer<GameObject> &newParent);
    // Virtual neighbors getters and setters.
    QSharedPointer<GameObject> &getNeighbor(Direction direction, int offset = 0) const;
    QList<QSharedPointer<GameObject>> &getAllNeighbors(int offset = 0) const;
    void actionTriggered(QSharedPointer<GameObject> &object, QSharedPointer<Behavior> action) const;

private:
    QSharedPointer<GameObject> m_parentObject;
};

#endif // LEAFOBJECT_H
