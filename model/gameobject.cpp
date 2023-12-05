#include "gameobject.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

QSharedPointer<GameObject>&
GameObject::getNeighbor(Direction direction, int offset) const {
}

QList<QSharedPointer<GameObject>>&
GameObject::getAllNeighbors(int offset) const {
}

void GameObject::actionTriggered(
    QSharedPointer<GameObject>& object,
    QSharedPointer<Behavior> action) const {
}

QList<QMap<GameObject::DataRole, QVariant>> GameObject::getAllData() {
}

QVariant GameObject::getData(DataRole role) {
}

bool GameObject::setData(DataRole role, const QVariant& value) {
}

int GameObject::dataCount() {
}
