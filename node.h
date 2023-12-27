#ifndef NODE_H
#define NODE_H

#include <world.h>

struct Node : public Tile {
    float f = 0.0f, g = 0.0f, h = 0.0f;
    bool visited = false;
    Node* prev = nullptr;

    Node(int x, int y, float val) : Tile(x, y, val) {}


    // Function to update the 'g' value
    void updateG(Node* parentNode) {
        // Accumulate the parent's 'g' and the cost of this tile
        // The cost of the tile can be its value or a custom cost based on your game logic
        this->g = parentNode->g + this->getValue(); // Adjust this calculation as needed
    }

    // Function to calculate the heuristic 'h'
    void calculateH(Node* endNode) {
        // Example: using Manhattan distance for heuristic calculation
        // Adjust the heuristic as per your game's requirements
        this->h = std::abs(endNode->getXPos() - this->getXPos()) + std::abs(endNode->getYPos() - this->getYPos());
    }

    // Function to update the 'f' value
    void updateF() {
        this->f = this->g + this->h;
    }

};

#endif // NODE_H
