#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include "vectorlight.h"

class Grid {
public:
    Grid(int w, int h, int numColors, int numTries);
    int getWidth();
    Tile* getTile(int row, int col);
    int getMaxTries();
    int getTries();
    void setTries(int numTries);
    bool isComplete();
    void updateColors(Tile* T, int startColor, int newColor);
    void print();
    void clearVect();
private:
    Tile** arr;
    int width;
    int height;
    int tries;
    int maxTries;
    VectorLight<Tile*> checkVect; // please work
};

#endif // GRID_H
