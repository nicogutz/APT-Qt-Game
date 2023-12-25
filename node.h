#ifndef NODE_H
#define NODE_H

#include "world.h" // Ensure this is the correct path

struct Node : public Tile {
    float f = 0.0f, g = 0.0f, h = 0.0f;
    bool visited = false;
    Node* prev = nullptr;

    Node(int x, int y, float val) : Tile(x, y, val) {}

    // Getters
    float getF() const { return f; }
    float getG() const { return g; }
    float getH() const { return h; }
    bool isVisited() const { return visited; }
    Node* getPrev() const { return prev; }

    // Setters
    void setF(float newValue) { f = newValue; }
    void setG(float newValue) { g = newValue; }
    void setH(float newValue) { h = newValue; }
    void setVisited(bool newVisited) { visited = newVisited; }
    void setPrev(Node* newPrev) { prev = newPrev; }
};

#endif // NODE_H
