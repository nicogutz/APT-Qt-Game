#include "gameobject.h"

GameObject::~GameObject() {
}

QVector<QMap<GameObject::DataRole, QVariant>> GameObject::getAllData() {
}

QVariant GameObject::getData(DataRole role) {
}

bool GameObject::setData(DataRole role, const QVariant &value) {
}

int GameObject::dataCount() {
}
