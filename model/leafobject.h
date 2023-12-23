#ifndef LEAFOBJECT_H
#define LEAFOBJECT_H

#include "gameobject.h"

class LeafObject : public GameObject {
public:
    LeafObject(QMap<std::type_index, QSharedPointer<Behavior>> behaviors,
               QMap<DataRole, QVariant> data,
               QSharedPointer<GameObject> parent = nullptr)
        : GameObject(behaviors, data)
        , m_parentObject(parent) {};

    // Parent getters and setters
    const QSharedPointer<GameObject> getParent() const;
    bool setParent(QSharedPointer<GameObject> newParent);

    // Virtual neighbors getters and setters.
    const QSharedPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const override;
    const QList<QSharedPointer<GameObject>> getAllNeighbors(int offset = 0) const override;

private:
    QSharedPointer<GameObject> m_parentObject;
};

#endif // LEAFOBJECT_H
