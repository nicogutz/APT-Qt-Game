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
                    auto *gameObj = qobject_cast<GameObject *>(obj);
                    connect(gameObj, &GameObject::dataChanged, this, &GameObjectModel::dataChanged);
                    connect(this, &GameObjectModel::tick, gameObj, &GameObject::tick);
                }
            }
        }
    };
    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> &getBehavior(int x, int y, ObjectType type) const {
        return m_world[x][y]->getBehavior<T>(type);
    };

    template <typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(int x, int y, ObjectType type, QSharedPointer<T> behavior) {
        return m_world[x][y]->setBehavior<T>(type, behavior);
    };

    QPointer<GameObject> getObject(int x, int y, ObjectType type) const;
    void setItem(int x, int y, QPointer<GameObject> object);
    int getRowCount() const;
    int getColumnCount() const;
    const QPointer<GameObject> getNeighbor(QPoint location, double direction, int offset) const;
    QList<QList<QMap<DataRole, QVariant>>> getAllData(bool) const;
    QList<QList<QList<QMap<DataRole, QVariant>>>> getAllData() const;

    QList<QPointer<GameObject>> getObject(ObjectType type) const;

private:
    QList<QList<QPointer<GameObject>>> m_world;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
    void tick();
};

#endif // GAMEOBJECTMODEL_H
