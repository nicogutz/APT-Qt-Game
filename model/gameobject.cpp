#include "gameobject.h"
#include "gameobjectmodel.h"

#include <QChar>

const QPointer<GameObject> GameObject::getNeighbor(Direction direction, int offset) const {
    if(auto prt = qobject_cast<GameObject *>(parent())) {
        return prt->getNeighbor(direction, offset);
    }
    return qobject_cast<GameObjectModel *>(parent())->getNeighbor(m_objectData[DataRole::Position].toPoint(), direction, offset);
}

const QList<QPointer<GameObject>> GameObject::getAllNeighbors(int offset) const {
    // I think this ended up looking pretty sweet.
    auto list = QList<QPointer<GameObject>>();
    for(Direction dir : EnumDirectionVector) {
        list.append(getNeighbor(dir, offset));
    }
    return list;
}

bool GameObject::eventFilter(QObject *watched, QEvent *event) {
    if(event->type() == QEvent::ParentChange) {
    }
    return QObject::eventFilter(watched, event);
}

void GameObject::setData(DataRole role, QVariant value) {
    auto data = getData();
    Direction dir = value.toInt() > data[role].toInt() ? Direction::Up : Direction::Down;

    data[role] = value;
    data[DataRole::LatestChange] = QVariant::fromValue<DataRole>(role);
    data[DataRole::ChangeDirection] = QVariant::fromValue<Direction>(dir);

    emit dataChanged(data);
}

const QPointer<GameObject> GameObject::findChild(ObjectType type) {
    return QObject::findChild<GameObject *>(QChar((char)type));
}

QVariant GameObject::getData(DataRole role) const {
    return m_objectData[role];
}

QMap<DataRole, QVariant> GameObject::getData() const {
    return m_objectData;
}
