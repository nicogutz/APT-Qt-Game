#include "nodeobject.h"

QSharedPointer<GameObject> NodeObject::getChild(ObjectType type) const {
    return m_childObjects[type];
}

QList<QSharedPointer<GameObject>> NodeObject::getChildren() const {
    return m_childObjects.values();
}

QSharedPointer<GameObject> NodeObject::popChild(ObjectType type) {
    return m_childObjects.take(type);
}

bool NodeObject::insertChild(QSharedPointer<GameObject> object) {
    auto objType = static_cast<ObjectType>(object->getData(DataRole::Type).toInt());
    if(m_childObjects.contains(objType)) {
        return false;
    }
    m_childObjects[objType] = object;

    return true;
}

int NodeObject::childrenCount() const {
    return m_childObjects.count();
}

const QSharedPointer<GameObject> NodeObject::getNeighbor(Direction direction, int offset) const {
    QSharedPointer<GameObject> neighbor = m_neighbors[direction];
    for(int i = 0; i < offset; ++i) {
        neighbor = neighbor->getNeighbor(direction);
    }
    return neighbor;
}

const QList<QSharedPointer<GameObject>> NodeObject::getAllNeighbors(int offset) const {
    // I think this ended up looking pretty sweet.
    auto list = QList<QSharedPointer<GameObject>>();
    for(Direction dir : EnumDirectionVector) {
        list.append(getNeighbor(dir, offset));
    }
    return list;
}

QList<QSharedPointer<Behavior>> NodeObject::getAllBehaviors(std::type_index idx) const {
    auto list = GameObject::getAllBehaviors(idx);
    for(const auto &child : m_childObjects) {
        list.append(child->getBehavior(idx));
    }
    return list;
}
