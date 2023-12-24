#include "gameobjectmodel.h"

int GameObjectModel::getRowCount() const {
    return m_world.size();
}

int GameObjectModel::getColumnCount() const {
    return m_world[0].size();
}

QSharedPointer<GameObject> GameObjectModel::getObject(int row, int column, ObjectType type) const {
    auto tile = m_world[row][column];
    if(type == ObjectType::Tile) {
        return tile;
    }
    return tile->getChild(type);
}

QSharedPointer<GameObject> GameObjectModel::popObject(int row, int column, ObjectType type) {
    auto tile = m_world[row][column];
    if(type == ObjectType::Tile) {
        return m_world[row].takeAt(column);
    }
    return tile->popChild(type);
}

void GameObjectModel::setItem(int row, int column, QSharedPointer<GameObject> object) {
    if(object->getData(DataRole::Type).toInt() == static_cast<int>(ObjectType::Tile)) {
        m_world[row][column] = qSharedPointerObjectCast<NodeObject>(object);
        return;
    }
    m_world[row][column]->insertChild(object);
}
