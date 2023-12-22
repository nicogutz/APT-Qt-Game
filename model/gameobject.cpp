#include "gameobject.h"

const QList<QMap<DataRole, QVariant>> GameObject::getAllData() const {
    auto v = QList<QMap<DataRole, QVariant>>();
    v.append(m_objectData);
    return v;
}

const QVariant GameObject::getData(DataRole role) const {
    return m_objectData[role];
}

bool GameObject::setData(DataRole role, const QVariant &value) {
    m_objectData.insert(role, value);
    return true;
}

int GameObject::dataCount() const {
    return m_objectData.size();
}
