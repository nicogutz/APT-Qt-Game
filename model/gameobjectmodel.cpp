#include "gameobjectmodel.h"
#include <math.h>
int GameObjectModel::getRowCount() const {
    return m_world.size();
}

int GameObjectModel::getColumnCount() const {
    return m_world[0].size();
}

const QPointer<GameObject> GameObjectModel::getNeighbor(QPoint location, Direction direction, int offset) const {
    double angleRad = ((int)direction) * M_PI / 180;
    int offsetNew = offset + 1;
    return m_world[location.x() + (offsetNew * round(cos(angleRad)))][location.y() + (offsetNew * round(sin(angleRad)))];
}

QPointer<GameObject> GameObjectModel::getObject(int row, int column, ObjectType type) const {
    auto tile = m_world[row][column];
    if(type == ObjectType::Tile) {
        return tile;
    }
    return tile->findChild(type);
}

void GameObjectModel::setItem(int row, int column, QPointer<GameObject> object) {
    if(object->getData(DataRole::Type).toInt() == static_cast<int>(ObjectType::Tile)) {
        delete m_world[row][column];
        m_world[row][column] = object;
        return;
    }
    object->setParent(m_world[row][column]);
}
