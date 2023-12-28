#pragma once
#ifndef GAMEOBJECTMODEL_H
#define GAMEOBJECTMODEL_H

#include "gameobject.h"
#include <QPoint>

class GameObjectModel : public QObject {
    Q_OBJECT
public:
    GameObjectModel(QList<QList<QPointer<GameObject>>> world) {
        m_world = world;
        for(const auto &row : m_world) {
            for(const auto &tile : row) {
                tile->setParent(this);
                connect(tile, &GameObject::dataChanged, this, &GameObjectModel::dataChanged);
                for(const auto &obj : tile->children()) {
                    connect(qobject_cast<GameObject *>(obj), &GameObject::dataChanged, this, &GameObjectModel::dataChanged);
                }
            }
        }
    };
    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> &getBehavior(int row, int column, ObjectType type) const {
        return m_world[row][column]->getBehavior<T>(type);
    };

    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(int row, int column, ObjectType type, QSharedPointer<T> behavior) {
        return m_world[row][column]->setBehavior<T>(type, behavior);
    };

    QPointer<GameObject> getObject(int row, int column, ObjectType type) const;
    void setItem(int row, int column, QPointer<GameObject> object);
    int getRowCount() const;
    int getColumnCount() const;
    const QPointer<GameObject> getNeighbor(QPoint location, Direction direction, int offset) const;
    QList<QList<QList<QMap<DataRole, QVariant>>>> getAllData() const;

private:
    QList<QList<QPointer<GameObject>>> m_world;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
    void tick(int);
};

#endif // GAMEOBJECTMODEL_H
