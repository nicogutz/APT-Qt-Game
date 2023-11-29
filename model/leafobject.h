#ifndef LEAFOBJECT_H
#define LEAFOBJECT_H

#include "gameobject.h"

class LeafObject : public GameObject {
public:
    LeafObject();
    // Parent getters and setters
    QSharedPointer<GameObject>& getParent() const;
    bool setParent(const QSharedPointer<GameObject>& newParent);
    // Virtual neighbors getters and setters.
    QSharedPointer<GameObject>& getNeighbor(Direction direction) const;
    QSharedPointer<GameObject>& getAllNeighbors() const;
    void actionTriggered(QSharedPointer<GameObject>& object, Behavior action) const;

private:
    QSharedPointer<GameObject> m_parentObject;
};

#endif // LEAFOBJECT_H
