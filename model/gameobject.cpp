#include "gameobject.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

QSharedPointer<GameObject> GameObject::getParent() {
}

QSharedPointer<GameObject> GameObject::getChild(ObjectType type) {
}

int GameObject::getChildrenCount() const {
}

bool GameObject::insertChild(GameObject object) {
}

bool GameObject::removeChild(ObjectType type) {
}

QSharedPointer<QVariant> GameObject::getData(DataRole role) const {
}

bool GameObject::setData(DataRole role, const QVariant& value) {
}

int GameObject::dataCount() const {
}

template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type> QSharedPointer<T> GameObject::getBehavior() {
}

template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type> QSharedPointer<T> GameObject::getBehavior(ObjectType child) {
}
