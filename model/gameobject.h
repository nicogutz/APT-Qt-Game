#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVariant>
#include <typeindex>

#include <model/behaviors/behavior.h>

class GameObject {
public:
    enum class ObjectType {
        Tile = 0,
        Doorway = 1,
        HealthPack = 2,
        Protagonist = 50,
        Enemy = 100,
        PoisonEnemy = 101,
        FireEnemy = 102,
    };
    enum class DataRole {
        Type,

        Health,
        Energy,
        Strength,

        PoisonLevel,
        FireLevel,

        Visibility,

        X_Position,
        Y_Position,
        Orientation,
    };
    enum class Direction {
        TopLeft,
        Up,
        TopRight,
        Left,
        Right,
        BottomLeft,
        Bottom,
        BottomRight,
    };

    explicit GameObject();
    ~GameObject();

    // Virtual neighbors getters and setters.
    virtual QSharedPointer<GameObject>&
    getNeighbor(Direction direction, int offset = 0) const = 0;
    virtual QList<QSharedPointer<GameObject>>&
    getAllNeighbors(int offset = 0) const = 0;
    virtual void actionTriggered(
        QSharedPointer<GameObject>& object,
        QSharedPointer<Behavior> action) const = 0;

    // Data getters and setters
    QVector<QMap<DataRole, QVariant>> getAllData();

    QVariant getData(DataRole role);

    bool setData(DataRole role, const QVariant& value);
    int dataCount();

    // Behavior getters and setters
    template<
        typename T,
        typename
        = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(QSharedPointer<Behavior> behavior) {};
    template<
        typename T,
        typename
        = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T>& getBehavior() {};
    template<
        typename T,
        typename
        = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QVector<QSharedPointer<T>>& getAllBehaviors() {};

private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QMap<DataRole, QVariant> m_objectData;
};

#endif // GAMEOBJECT_H
