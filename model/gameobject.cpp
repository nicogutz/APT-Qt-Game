#include "gameobject.h"
#include "gameobjectmodel.h"

#include <QChar>
#include <iostream>

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

bool GameObject::event(QEvent *event) {
    if(event->type() == QEvent::ParentChange) {
        auto data = getData();
        data[DataRole::Position] = qobject_cast<GameObject *>(parent())->getData(DataRole::Position);
        data[DataRole::LatestChange] = QVariant::fromValue<DataRole>(DataRole::Position);
        data[DataRole::ChangeDirection] = getData(DataRole::Direction);
        qDebug() << "Moved To: (" << data[DataRole::Position].toPoint().x() << ", " << data[DataRole::Position].toPoint().y() << ")";
        qDebug() << "Direction: " << data[DataRole::ChangeDirection].toInt();

        emit dataChanged(data);
        return true;
    }

    return QObject::event(event);
}

void GameObject::setData(DataRole role, QVariant value) {
    m_objectData[role] = value;

    auto data = getData();
    Direction dir = value.toInt() > data[role].toInt() ? Direction::Up : Direction::Down;
    qDebug() << "Data Changed: " << (int)role << " : " << m_objectData[role].toInt() << ":" << (int)dir;
    if(parent() && parent()->inherits("GameObject")) {
        data[DataRole::Position] = qobject_cast<GameObject *>(parent())->getData(DataRole::Position);
    }
    data[DataRole::LatestChange] = QVariant::fromValue<DataRole>(role);
    data[DataRole::ChangeDirection] = QVariant::fromValue<Direction>(dir);
    emit dataChanged(data);
}

void GameObject::setData(QList<QPair<DataRole, QVariant>> data) {
    for(const auto &pair : data) {
        m_objectData[pair.first] = pair.second;
    }
}

const QPointer<GameObject> GameObject::findChild(ObjectType type) {
    auto children = findChildren<GameObject *>();
    for(auto child : children) {
        if(child->getData(DataRole::Type).value<ObjectType>() == type) {
            return child;
        }
    }
    return nullptr;
}

QVariant GameObject::getData(DataRole role) const {
    return m_objectData[role];
}

QMap<DataRole, QVariant> GameObject::getData() const {
    return m_objectData;
}

QList<QMap<DataRole, QVariant>> GameObject::getAllData() const {
    QList<QMap<DataRole, QVariant>> list;
    list.append(getData());
    for(auto child : children()) {
        list.append(qobject_cast<GameObject *>(child)->getData());
    }
    return list;
}
