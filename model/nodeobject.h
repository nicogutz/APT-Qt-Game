#ifndef NODEOBJECT_H
#define NODEOBJECT_H

#include "gameobject.h"
class GameObjectModel;

class NodeObject : public GameObject {
public:
    NodeObject(QMap<std::type_index, QSharedPointer<Behavior>> behaviors,
               QMap<DataRole, QVariant> data)
        : GameObject(behaviors, data) {};

    // Children getters and setters
    QSharedPointer<GameObject> getChild(ObjectType type) const;
    QList<QSharedPointer<GameObject>> getChildren() const;
    QSharedPointer<GameObject> popChild(ObjectType type);
    bool insertChild(QSharedPointer<GameObject> object);
    int childrenCount() const;

    // GameObject interface
    const QSharedPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const override;
    const QList<QSharedPointer<GameObject>> getAllNeighbors(int offset = 0) const override;
    QList<QSharedPointer<Behavior>> getAllBehaviors(std::type_index idx) const override;

private:
    QMap<Direction, QSharedPointer<GameObject>> m_neighbors;
    QMap<ObjectType, QSharedPointer<GameObject>> m_childObjects;
    QSharedPointer<GameObjectModel> m_parentObject;
};

#endif // NODEOBJECT_H
