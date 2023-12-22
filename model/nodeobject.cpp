#include "nodeobject.h"

QSharedPointer<GameObject> &NodeObject::getChild(ObjectType type) const {
}

QList<QSharedPointer<const GameObject>> &NodeObject::getChildren() const {
}

QSharedPointer<GameObject> NodeObject::popChild(ObjectType type) {
}

bool NodeObject::insertChild(QSharedPointer<GameObject> object) {
}

int NodeObject::getChildrenCount() const {
}

QSharedPointer<GameObject> &NodeObject::getNeighbor(Direction direction, int offset) const {
}

QList<QSharedPointer<GameObject>> &NodeObject::getAllNeighbors(int offset) const {
}

void NodeObject::actionTriggered(
  QSharedPointer<GameObject> &object, QSharedPointer<Behavior> action) const {
}
