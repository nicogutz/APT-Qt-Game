#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QEvent>
#include <QPointer>
#include <QVariant>
#include <typeindex>

#include "publicenums.h"
#include "model/behaviors/behavior.h"

class GameObject : public QObject {
    Q_OBJECT
public:
    GameObject(QMap<DataRole, QVariant> objectData)
        : m_objectData(objectData) {};
    GameObject() { m_objectData = QMap<DataRole, QVariant>(); };

    ~GameObject() {};
    // Extra child getter
    const QPointer<GameObject> findChild(ObjectType type);

    // Data getters and setters.
    QVariant getData(DataRole role) const;
    QMap<DataRole, QVariant> getData() const;
    QList<QMap<DataRole, QVariant>> getAllData() const;

    void setData(DataRole role, QVariant value);
    void setData(QList<QPair<DataRole, QVariant>> data);

    // Neighbors getters and setters.
    const QPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const;
    const QList<QPointer<GameObject>> getAllNeighbors(int offset = 0) const;

    // Behavior getters and setters
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    void setBehavior(QSharedPointer<T> behavior) {
        m_behaviors[typeid(T)] = behavior;
    }

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> getBehavior() const {
        auto behavior = m_behaviors[typeid(T)];
        return qSharedPointerDynamicCast<T>(behavior);
    }

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QList<QSharedPointer<T>> getAllBehaviors() const {
        auto list = QList<QSharedPointer<T>>();
        list.append(qSharedPointerDynamicCast<T>(m_behaviors[typeid(T)]));

        for(auto *child : findChildren<GameObject *>()) {
            list.append(qSharedPointerDynamicCast<T>(child->getBehavior<T>()));
        }
        return list;
    };

    // QObject interface
    bool event(QEvent *event) override;

private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QMap<DataRole, QVariant> m_objectData;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
};

#endif // GAMEOBJECT_H
