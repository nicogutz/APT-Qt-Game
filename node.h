#ifndef NODE_H
#define NODE_H

#include "publicenums.h"
#include <world.h>
#include <QMap>
#include <QMap>
#include <QVariant>
struct Node : public Tile {
    float f = 0.0f, g = 0.0f, h = 0.0f;
    bool visited = false;
    Node *prev = nullptr;

    Node(int x, int y, float val)
        : Tile(x, y, val) { }
    Node(const Node &n)
        : Tile(n.getXPos(), n.getYPos(), n.getValue()) {};
    Node()
        : Tile(0, 0, 0) {};

    Node(const QMap<DataRole, QVariant> &obj)
        : Tile(
          obj[DataRole::Position].toPoint().x(),
          obj[DataRole::Position].toPoint().y(),
          obj[DataRole::Energy].toFloat()) {};

    Node operator=(const Node &n) {
        return Node(n);
    }
};

#endif // NODE_H
