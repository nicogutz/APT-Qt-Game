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
    QSharedPointer<GameObject> &getChild(ObjectType type) const;
    QList<QSharedPointer<const GameObject>> &getChildren() const;
    QSharedPointer<GameObject> popChild(ObjectType type);
    bool insertChild(QSharedPointer<GameObject> object);
    int getChildrenCount() const;

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> &getBehavior(ObjectType child) {

    };
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QList<QSharedPointer<T>> &getAllBehaviors(ObjectType child) const {

    };
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QList<QSharedPointer<T>> &getAllBehaviors() const {

    };

    // GameObject interface
    QSharedPointer<GameObject> &getNeighbor(Direction direction, int offset = 0) const override;
    QList<QSharedPointer<GameObject>> &getAllNeighbors(int offset = 0) const override;
    void actionTriggered(QSharedPointer<GameObject> &object, QSharedPointer<Behavior> action) const;

private:
    QMap<Direction, QSharedPointer<GameObject>> m_neighbors;
    QMap<ObjectType, QSharedPointer<GameObject>> m_childObjects;
    QSharedPointer<GameObjectModel> m_parentObject;
};

#endif // NODEOBJECT_H
