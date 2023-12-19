#include "leafobject.h"



QSharedPointer<GameObject>& LeafObject::getParent() const {
}

bool LeafObject::setParent(const QSharedPointer<GameObject>& newParent) {
}

QSharedPointer<GameObject>& LeafObject::getNeighbor(Direction direction, int offset) const {
}

QList<QSharedPointer<GameObject>>& LeafObject::getAllNeighbors(int offset) const {
}

void LeafObject::actionTriggered(
    QSharedPointer<GameObject>& object, QSharedPointer<Behavior> action) const {
}
