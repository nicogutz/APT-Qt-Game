#ifndef NODEOBJECT_H
#define NODEOBJECT_H

#include "gameobject.h"

class NodeObject : public GameObject {
    Q_OBJECT
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

    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> getBehavior(ObjectType type) const {
        return m_childObjects[type]->getBehavior<T>();
    };
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(ObjectType type, QSharedPointer<T> behavior) {
        return m_childObjects[type]->setBehavior<T>(behavior);
    }

    // GameObject interface
    const QSharedPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const override;
    const QList<QSharedPointer<GameObject>> getAllNeighbors(int offset = 0) const override;
    QList<QSharedPointer<Behavior>> getAllBehaviors(std::type_index idx) const override;

private:
    QMap<Direction, QSharedPointer<GameObject>> m_neighbors;
    QMap<ObjectType, QSharedPointer<GameObject>> m_childObjects;
};

#endif // NODEOBJECT_H
