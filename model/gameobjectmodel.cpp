#include "gameobjectmodel.h"
#include <math.h>
int GameObjectModel::getRowCount() const {
    return m_world.size();
}

int GameObjectModel::getColumnCount() const {
    return m_world[0].size();
}

const QPointer<GameObject> GameObjectModel::getNeighbor(QPoint location, double direction, int offset) const {
    double angleRad = direction * M_PI / 180;
    offset++;
    // Took me a while to come up with this. It transforms any angle to an acute angle using mod 45.
    // Since we know the adjacent side is always "offset" long we multiply it by the tan.
    // The ternary fixes the issue that mod45 is 0 :(
    double b = abs(std::fmod(direction, 90) - 45) < 1e-6 ? offset : offset * tan((std::fmod(direction, 45)) * M_PI / 180);

    // Calculate the length of the hypothenuse. c = sqrt(a^2+b^2)
    double c = sqrt(b * b + offset * offset);

    // More angle kajiggery, our world is flipped w.r.t. the list in the y-ax
    // Therefore flipping the angle flips the y axis and not the x axis :)
    int x = location.x() + round((c * cos(-angleRad)));
    int y = location.y() + round((c * sin(-angleRad)));

    // No access allowed in the void
    if(0 > x || 0 > y || x >= getRowCount() || y >= getColumnCount()) {
        return QPointer<GameObject>(nullptr);
    }
    // Im pretty sure this won't cause any issues :shrug:
    return m_world.at(x).at(y);
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

QList<QPointer<GameObject>> GameObjectModel::getObject(ObjectType type) const {
    QList<QPointer<GameObject>> list {};
    for(int x = 0; x < getRowCount(); ++x) {
        for(int y = 0; y < getColumnCount(); ++y) {
            if(auto tile = getObject(x, y, type)) {
                list.append(tile);
            }
        }
    }
    return list;
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
