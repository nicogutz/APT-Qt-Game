#ifndef NODEOBJECT_H
#define NODEOBJECT_H

#include "gameobject.h"
class GameObjectModel;

class NodeObject : public GameObject {
public:
    NodeObject();
    // Children getters and setters
    QSharedPointer<GameObject>& getChild(ObjectType type) const;
    QVector<QSharedPointer<const GameObject>>& getChildren() const;
    QSharedPointer<GameObject> popChild(ObjectType type);
    bool insertChild(QSharedPointer<GameObject> object);
    int getChildrenCount() const;

    template<typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T>& getBehavior(ObjectType child) {

    };
    template<typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QVector<QSharedPointer<T>>& getAllBehaviors(ObjectType child) const {

    };
    template<typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QVector<QSharedPointer<T>>& getAllBehaviors() const {

    };

    // GameObject interface
    QSharedPointer<GameObject>& getNeighbor(Direction direction, int offset = 0) const;
    QList<QSharedPointer<GameObject>>& getAllNeighbors(int offset = 0) const;
    void actionTriggered(QSharedPointer<GameObject>& object, QSharedPointer<Behavior> action) const;

private:
    QMap<Direction, QSharedPointer<GameObject>> m_neighbors;
    QMap<ObjectType, QSharedPointer<GameObject>> m_childObjects;
    QSharedPointer<GameObjectModel> m_parentObject;
};

#endif // NODEOBJECT_H
