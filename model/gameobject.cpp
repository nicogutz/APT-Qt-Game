#include "gameobject.h"

QMap<DataRole, QVariant> GameObject::getAllData() const {
    return m_objectData;
}

const QVariant GameObject::getData(DataRole role) const {
    return m_objectData[role];
}

bool GameObject::setData(DataRole role, QVariant value) {
    auto data = getAllData();
    Direction dir = value.toInt() > data[role].toInt() ? Direction::Up : Direction::Down;

    m_objectData[role] = value;
    m_objectData[DataRole::LatestChange] = QVariant(static_cast<int>(role));
    m_objectData[DataRole::ChangeDirection] = QVariant(static_cast<int>(dir));

    emit dataChanged(getAllData());
    return true;
}

int GameObject::dataCount() const {
    return m_objectData.size();
}

QList<QSharedPointer<Behavior>> GameObject::getAllBehaviors(std::type_index idx) const {
    return QList<QSharedPointer<Behavior>>({getBehavior(idx)});
}
