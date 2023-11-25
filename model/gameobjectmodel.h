#pragma once
#ifndef GAMEOBJECTMODEL_H
#define GAMEOBJECTMODEL_H

#include "gameobject.h"

class GameObjectModel : public QObject {
    Q_OBJECT
public:
    GameObjectModel();

    QVariant getData(int row, int column, GameObject::ObjectType type, GameObject::DataRole role) const;
    bool setData(int row, int column, GameObject::ObjectType type, GameObject::DataRole role, QVariant data);

    template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> getBehavior(int row, int column, GameObject::ObjectType type);

    template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> setBehavior(int row, int column, GameObject::ObjectType type);

    int getRowCount() const;
    int getColumnCount() const;
public slots:
    void objectChanged(QSharedPointer<GameObject> object, GameObject::DataRole role);
    void childMoved(QSharedPointer<GameObject> from, QSharedPointer<GameObject> to, GameObject::DataRole role);

private:
    bool insertColumns(int position, int columns);
    bool removeColumns(int position, int columns);
    bool insertRows(int position, int rows);
    bool removeRows(int position, int rows);
    QSharedPointer<GameObject> getItem(int row, int column, GameObject::ObjectType type) const;
};

#endif // GAMEOBJECTMODEL_H
