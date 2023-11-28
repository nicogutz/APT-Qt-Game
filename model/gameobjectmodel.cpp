#include "gameobjectmodel.h"
GameObjectModel::GameObjectModel() {
}

QVariant GameObjectModel::getData(int row, int column, GameObject::ObjectType type, GameObject::DataRole role) const {
}

int GameObjectModel::getRowCount() const {
}

int GameObjectModel::getColumnCount() const {
}

void GameObjectModel::objectChanged(QSharedPointer<GameObject> object, GameObject::DataRole role)
{

}

void GameObjectModel::childMoved(QSharedPointer<GameObject> from, QSharedPointer<GameObject> to, GameObject::DataRole role)
{

}

bool GameObjectModel::setData(int row, int column, GameObject::ObjectType type, GameObject::DataRole role, QVariant data) {
}

bool GameObjectModel::insertColumns(int position, int columns) {
}

bool GameObjectModel::removeColumns(int position, int columns) {
}

bool GameObjectModel::insertRows(int position, int rows) {
}

bool GameObjectModel::removeRows(int position, int rows) {
}

QSharedPointer<GameObject> GameObjectModel::getItem(int row, int column, GameObject::ObjectType type) const {
}

template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
QSharedPointer<T> GameObjectModel::getBehavior(int row, int column, GameObject::ObjectType type) {
}

template<typename T, typename std::enable_if<std::is_base_of<Behavior, T>::value>::type>
QSharedPointer<T> GameObjectModel::setBehavior(int row, int column, GameObject::ObjectType type) {
}
