#pragma once
#ifndef GAMEOBJECTMODEL_H
#define GAMEOBJECTMODEL_H

#include "nodeobject.h"

class GameObjectModel : public QObject {
    Q_OBJECT
public:
    GameObjectModel() {};
    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> &getBehavior(int row, int column, ObjectType type) const {
        return m_world[row][column]->getBehavior<T>(type);
    };

    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(int row, int column, ObjectType type, QSharedPointer<T> behavior) {
        return m_world[row][column]->setBehavior<T>(type, behavior);
    };

    QSharedPointer<GameObject> getObject(int row, int column, ObjectType type) const;
    QSharedPointer<GameObject> popObject(int row, int column, ObjectType type);
    void setItem(int row, int column, QSharedPointer<GameObject> object);

    int getRowCount() const;
    int getColumnCount() const;

private:
    QList<QList<QSharedPointer<NodeObject>>> m_world;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
};

#endif // GAMEOBJECTMODEL_H
