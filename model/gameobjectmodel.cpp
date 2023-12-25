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
    int x = location.x() + ((offset + 1) * round(cos(angleRad)));
    int y = location.y() - ((offset + 1) * round(sin(angleRad)));
    if(0 > x || 0 > y || x >= getRowCount() || y >= getColumnCount()) {
        return QPointer<GameObject>(nullptr);
    }
    return m_world[x][y];
}

QList<QList<QList<QMap<DataRole, QVariant>>>> GameObjectModel::getAllData() const {
    QList<QList<QList<QMap<DataRole, QVariant>>>> list;
    for(int i = 0; i < getRowCount(); ++i) {
        list.append(QList<QList<QMap<DataRole, QVariant>>>());
        for(int j = 0; j < getColumnCount(); ++j) {
            list[i].append(m_world[i][j]->getAllData());
        }
    }
    return list;
}

QPointer<GameObject> GameObjectModel::getObject(int row, int column, ObjectType type) const {
    if(row > getRowCount() || column > getColumnCount()) {
        return QPointer<GameObject>(nullptr);
    }

    auto tile = m_world[row][column];
    if(type == ObjectType::Tile) {
        return tile;
    }

    return tile->findChild(type);
}

void GameObjectModel::setItem(int row, int column, QPointer<GameObject> object) {
    if(row > getRowCount() || column > getColumnCount()) {
        throw "Cannot set outside range";
    }

    if(object->getData(DataRole::Type).value<ObjectType>() == ObjectType::Tile) {
        delete m_world[row][column];
        m_world[row][column] = object;
        return;
    }

    object->setParent(m_world[row][column]);
}
