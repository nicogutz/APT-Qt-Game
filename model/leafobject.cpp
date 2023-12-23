#include "leafobject.h"

const QSharedPointer<GameObject> LeafObject::getParent() const {
    return m_parentObject;
}

bool LeafObject::setParent(QSharedPointer<GameObject> newParent) {
    m_parentObject = newParent;
    auto data = getAllData();
    data[DataRole::Position] = QVariant(m_parentObject->getData(DataRole::Position));
    data[DataRole::LatestChange] = QVariant(static_cast<int>(DataRole::Position));
    data[DataRole::ChangeDirection] = getData(DataRole::Direction);
    emit dataChanged(data);
    return true;
}

const QSharedPointer<GameObject> LeafObject::getNeighbor(Direction direction, int offset) const {
    return m_parentObject->getNeighbor(direction, offset);
}

const QList<QSharedPointer<GameObject>> LeafObject::getAllNeighbors(int offset) const {
    return m_parentObject->getAllNeighbors(offset);
}
