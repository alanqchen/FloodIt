#include <FEHLCD.h>
#include <LCDColors.h>
#include <stdlib.h>
#include "grid.h"
#include "tile.h"
#include "vectorlight.cpp"
#include "vectorlight.h"

// Contructor w/ params
Grid::Grid(int w, int h, int numColors, int numTries) {
    // Init color list
    int colorList[10] = {FEHLCD::Scarlet,DARKGREEN,DARKTURQUOISE,PURPLE,CHOCOLATE,GOLD,KHAKI,LIGHTGREEN,LAWNGREEN,ORANGE};
    // Set random seed
    srand(TimeNow());
    // Set width, height, and max tries
    width = w;
    height = h;
    maxTries = numTries;
    // Init tries to 0
    tries = 0;
    // Fill 2D array with tiles
    arr = new Tile*[height];
    for(int i = 0; i < height; i++) {
        arr[i] = new Tile[width]; // Create tile array
    }
    // Set the variables of each tile in array
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            // Get random color index from list within set range
            int colorIndex = rand() % numColors; // 0 to numColors-1
            arr[i][j].setColor(colorList[colorIndex]);
            arr[i][j].setRow(i); // Set row
            arr[i][j].setCol(j); // Set column
            arr[i][j].setChecked(false); // Set check flag
        }
    }
}

// Get grid width in terms of tiles
int Grid::getWidth() {
    return width;
}

// Get grid height in terms of tiles
int Grid::getHeight() {
    return height;
}

// Get pointer to tile at position
Tile* Grid::getTile(int row, int col) {
    return &arr[row][col];
}

// Get max number of tries
int Grid::getMaxTries() {
    return maxTries;
}

// Get current number of tries
int Grid::getTries() {
    return tries;
}

// Set number of tries
void Grid::setTries(int numTries) {
    tries = numTries;
}

// Check if grid is complete
bool Grid::isComplete() {
    // Store check vector size before emptying
    int size = checkVect.size();
    // Empty check vector while setting each tile's check flag to false
    while(!checkVect.empty()) {
        Tile* t = checkVect.pop_back();
        t->setChecked(false);
    }
    int cmpColor = getTile(0, 0)->getColor();
    // Test for early exit using check vector size
    //   (Complete grid implies check vector size is width*height)
    if(size != width*height)
        return false;
    // Loop through every tile in grid
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(getTile(i, j)->getColor() != cmpColor) {
                // Return false, a tile has a different color
                return false;
            }
        }
    }
    // Return true, all tiles have the same color
    return true;
}

// Update grid's colors
void Grid::updateColors(Tile* T, int startColor, int newColor) {
    // Return if tile was checked
    if(T->wasChecked())
        return;
    // If it wasn't, push tile onto check vector
    checkVect.push_back(T);
    // Set tile's check flag to true
    T->setChecked(true);
    // Check if tile's color is the same as the top left tile's old color
    if(T->getColor() != startColor)
        return; // return if it isn't
    // Set tile's color to the new color
    T->setColor(newColor);
    // Print updated grid
    print();
    // Check if the position below the tile is a valid position and
    //   if it is, call updateColors on the tile if it hasn't been checked
    if(T->getRow()-1 >= 0 && !arr[T->getRow()-1][T->getCol()].wasChecked())
        updateColors(&arr[T->getRow()-1][T->getCol()], startColor, newColor);

    // Check if the position above the tile is a valid position and
    //   if it is, call updateColors on the tile if it hasn't been checked
    if(T->getRow()+1 < width && !arr[T->getRow()+1][T->getCol()].wasChecked())
        updateColors(&arr[T->getRow()+1][T->getCol()], startColor, newColor);

    // Check if the position left of the tile is a valid position and
    //   if it is, call updateColors on the tile if it hasn't been checked
    if(T->getCol()-1 >= 0 && !arr[T->getRow()][T->getCol()-1].wasChecked())
        updateColors(&arr[T->getRow()][T->getCol()-1], startColor, newColor);

    // Check if the position right of the tile is a valid position and
    //   if it is, call updateColors on the tile if it hasn't been checked
    if(T->getCol()+1 < width && !arr[T->getRow()][T->getCol()+1].wasChecked())
        updateColors(&arr[T->getRow()][T->getCol()+1], startColor, newColor);

    return;
}

// Print grid
void Grid::print() {
    // Set color to black
    LCD.SetFontColor(BLACK);
    // Draw outer black edge around grid
    LCD.DrawRectangle((160-(((180/height)*width)/2)), 25, ((180/height)*width)+1, 181);
    // Loop thhrough every tile
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            // Print rectange representing tile's position and color
            LCD.SetFontColor(getTile(i, j)->getColor());
            LCD.FillRectangle((160-(((180/height)*width)/2))+1+(j*180/height),26+(i*180/height), 180/height, 180/height);
        }
    }
    // Check if tries is less than 10 (only one digit wide)
    if(tries/10 == 0)
        LCD.WriteAt(tries, 142, 208); // Print tries close to '/'
    else
        LCD.WriteAt(tries, 130, 208); // Print tries a little further from '/'

    // Print '/"
    LCD.WriteAt("/", 154, 208);
    // Print max number of tries
    LCD.WriteAt(maxTries, 166, 208);
}

// Clear check vector
void Grid::clearVect() {
    checkVect.clear();
}
