#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVariant>
#include <typeindex>

#include <model/behaviors/behavior.h>
class GameObjectModel;

class GameObject {
public:
    enum ObjectType {
        Tile = 0,
        Doorway = 1,
        HealthPack = 2,
        Protagonist = 50,
        Enemy = 100,
        PoisonEnemy = 101,
        FireEnemy = 102,
        MovingEnemy = 103,
    };
    enum DataRole {
        Health,
        PoisonLevel,
        FireLevel,
        Energy,
        X_Position,
        Y_Position,
        Visibility,
    };

    explicit GameObject();
    ~GameObject();
    QSharedPointer<GameObject> getParent();
    QSharedPointer<GameObject> setParent(QSharedPointer<GameObject> newParent);
    QSharedPointer<GameObjectModel> getModel();

    // Children getters and setters
    QSharedPointer<GameObject> getChild(ObjectType type);
    int getChildrenCount() const;
    bool insertChild(GameObject object);
    bool removeChild(ObjectType type);

    // Data getters and setters
    QSharedPointer<QVariant> getData(DataRole role) const;
    bool setData(DataRole role, const QVariant& value);
    int dataCount() const;

    // Behavior getters and setters
    template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type> QSharedPointer<T> setBehavior();
    template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type> QSharedPointer<T> getBehavior();
    template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type> QSharedPointer<T> getBehavior(ObjectType child);

private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QList<QSharedPointer<GameObject>> m_childObjects;
    QList<QVariant> m_objectData;
    QSharedPointer<GameObject> m_parentObject;
    QSharedPointer<GameObjectModel> m_model;
};

#endif // GAMEOBJECT_H
