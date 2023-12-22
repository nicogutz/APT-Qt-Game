#pragma once
#ifndef GAMEOBJECTMODEL_H
#define GAMEOBJECTMODEL_H

#include "gameobject.h"

class GameObjectModel : public QObject {
    Q_OBJECT
public:
    GameObjectModel() {};
    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> &getBehavior(int row, int column, ObjectType type) const;

    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(int row, int column, ObjectType type);

    int getRowCount() const;
    int getColumnCount() const;

private:
    QSharedPointer<GameObject> &getObject(int row, int column, ObjectType type) const;

    QVariant
    getData(int row, int column, ObjectType type, DataRole role) const;
    bool setData(
      int row, int column, ObjectType type, DataRole role, QVariant data);
    bool setItem(int row, int column, QSharedPointer<GameObject> type);

    bool insertColumns(int position, int columns);
    bool removeColumns(int position, int columns);
    bool insertRows(int position, int rows);
    bool removeRows(int position, int rows);
    QVector<QVector<QSharedPointer<GameObject>>> m_world;

signals:
    void actionExecuted(QSharedPointer<GameObject> &object, const QSharedPointer<Behavior> &action);
};

#endif // GAMEOBJECTMODEL_H
