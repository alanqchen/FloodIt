#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include "vectorlight.h"

class Grid {
public:
    Grid(int w, int h, int numColors, int numTries); // Contructor w/ params
    int getWidth(); // Get grid width in terms of tiles
    int getHeight(); // Get grid height in terms of tiles
    Tile* getTile(int row, int col); // Get pointer to tile at position
    int getMaxTries(); // Get max number of tries
    int getTries(); // Get current number of tries
    void setTries(int numTries); // Set number of tries
    bool isComplete(); // Check if grid is complete
    // Note: when calling updateColors, give it the pointer to the top left tile and it's color
    void updateColors(Tile* T, int startColor, int newColor); // Update grid's colors
    void print(); // Print grid
    void clearVect(); // Clear check vector
private:
    Tile** arr; // 2D array of tiles
    int width; // Width in terms of tiles
    int height; // Height in terms of tiles
    int tries; // Current num of tries
    int maxTries; // Max num of tries
    // Vector to store checked tiles pointers so that
    //   the flags can be reset later.
    VectorLight<Tile*> checkVect;
};

#endif // GRID_H
