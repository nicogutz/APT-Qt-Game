#ifndef NODE_H
#define NODE_H

#include <world.h>

struct Node : public Tile {
    float f = 0.0f, g = 0.0f, h = 0.0f;
    bool visited = false;
    Node* prev = nullptr;

    Node(int x, int y, float val) : Tile(x, y, val) {}



};

#endif // NODE_H
