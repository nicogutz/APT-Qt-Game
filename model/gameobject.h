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
        Direction,

        LatestChange,
        ChangeDirection,
    };
    enum class Direction {
        TopLeft = 45,
        Up = 90,
        TopRight = 135,
        Left = 180,
        Right = 0,
        BottomLeft = 225,
        Bottom = 270,
        BottomRight = 315,
    };
    GameObject();
    ~GameObject();

    // Virtual neighbors getters and setters.
    virtual QSharedPointer<GameObject> &
    getNeighbor(Direction direction, int offset = 0) const = 0;
    virtual QList<QSharedPointer<GameObject>> &
    getAllNeighbors(int offset = 0) const = 0;
    virtual void actionTriggered(
      QSharedPointer<GameObject> &object,
      QSharedPointer<Behavior> action) const = 0;

    // Data getters and setters
    QVector<QMap<DataRole, QVariant>> getAllData();
    QVariant getData(DataRole role);

    bool setData(DataRole role, const QVariant &value);
    int dataCount();

    // Behavior getters and setters
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(QSharedPointer<Behavior> behavior) {
        if(qSharedPointerDynamicCast<T>(behavior)) {
            throw "Not correct behavior";
        }
        m_behaviors[typeid(T)] = behavior;
        return true;
    };

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> &getBehavior() {
        return qSharedPointerDynamicCast<T>(m_behaviors[typeid(T)]);
    };

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QVector<QSharedPointer<T>> &getAllBehaviors() {
      //        return QVector<T>(getBehavior<T>());
    };

private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QMap<DataRole, QVariant> m_objectData;
};

#endif // GAMEOBJECT_H
