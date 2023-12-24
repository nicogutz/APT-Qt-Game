#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVariant>
#include <typeindex>

#include "publicenums.h"
#include "model/behaviors/behavior.h"

class GameObject : public QObject {
    Q_OBJECT
public:
    GameObject(QMap<std::type_index, QSharedPointer<Behavior>> behaviors,
               QMap<DataRole, QVariant> data)
        : m_behaviors(behaviors)
        , m_objectData(data) {};

    ~GameObject() {};

    // Virtual neighbors getters and setters.
    virtual const QSharedPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const = 0;
    virtual const QList<QSharedPointer<GameObject>> getAllNeighbors(int offset = 0) const = 0;

    // Data getters and setters
    QMap<DataRole, QVariant> getAllData() const;
    const QVariant getData(DataRole role) const;

    bool setData(DataRole role, QVariant value);
    int dataCount() const;

    // Behavior getters and setters
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    bool setBehavior(QSharedPointer<T> behavior) {
        m_behaviors[typeid(T)] = behavior;
        return true;
    }

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QSharedPointer<T> &getBehavior() const {
        return qSharedPointerDynamicCast<T>(getBehavior(typeid(T)));
    }
    const QSharedPointer<Behavior> getBehavior(std::type_index idx) const {
        return m_behaviors[idx];
    };

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QList<QSharedPointer<T>> getAllBehaviors() const {
        auto list = getAllBehaviors(typeid(T));
        auto newList = QList<QSharedPointer<T>>();
        for(const auto &behavior : list) {
            newList.append(qSharedPointerDynamicCast<T>(behavior));
        }
        return newList;
    };

    virtual QList<QSharedPointer<Behavior>> getAllBehaviors(std::type_index idx) const;

private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QMap<DataRole, QVariant> m_objectData;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
};

#endif // GAMEOBJECT_H
