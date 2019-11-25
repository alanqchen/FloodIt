#include <FEHLCD.h>
#include <LCDColors.h>
#include "grid.h"
#include "tile.h"
#include "vectorlight.cpp"
#include "vectorlight.h"

#include <stdlib.h>

Grid::Grid(int w, int numColors, int numTries) {
    int colorList[10] = {FEHLCD::Scarlet,DARKGREEN,DARKTURQUOISE,PURPLE,CHOCOLATE,GOLD,KHAKI,LIGHTGREEN,LAWNGREEN,ORANGE};
    width = w;
    maxTries = numTries;
    tries = 0;
    arr = new Tile*[width];
    for(int i = 0; i < width; i++) {
        arr[i] = new Tile[width];
    }
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            int colorIndex = rand() % numColors; // 0 to numColors-1
            arr[i][j].setColor(colorList[colorIndex]);
            arr[i][j].setRow(i);
            arr[i][j].setCol(j);
            arr[i][j].setChecked(false);
        }
    }
}

int Grid::getWidth() {
    return width;
}

Tile* Grid::getTile(int row, int col) {
    return &arr[row][col];
}

int Grid::getMaxTries() {
    return maxTries;
}

int Grid::getTries() {
    return tries;
}

void Grid::setTries(int numTries) {
    tries = numTries;
}

bool Grid::isComplete() {
    bool result = true;
    if(checkVect.size() != width*width)
        result = false;
    while(!checkVect.empty()) {
        Tile* t = checkVect.pop_back();
        int cmpColor = t->getColor();
        t->setChecked(false);
        if(t->getColor() != cmpColor)
            result = false;
    }
    return result;
}

void Grid::updateColors(Tile* T, int startColor, int newColor) {
    if(T->wasChecked())
        return;
    checkVect.push_back(T);
    T->setChecked(true);
    if(T->getColor() != startColor)
        return;
    T->setColor(newColor);
    print(); // might be expensive
    // Bounds checking
    if(T->getRow()-1 >= 0)
        updateColors(&arr[T->getRow()-1][T->getCol()], startColor, newColor);
    if(T->getRow()+1 < width)
        updateColors(&arr[T->getRow()+1][T->getCol()], startColor, newColor);
    if(T->getCol()-1 >= 0)
        updateColors(&arr[T->getRow()][T->getCol()-1], startColor, newColor);
    if(T->getCol()+1 < width)
        updateColors(&arr[T->getRow()][T->getCol()+1], startColor, newColor);
    return;
}

void Grid::print() {
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(70, 25, 182, 182);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            LCD.SetFontColor(getTile(i, j)->getColor());
            LCD.FillRectangle(71+(i*180/width),26+(j*180/width), 180/width, 180/width); // Please work
        }
    }
    if(tries/10 == 0)
        LCD.WriteAt(tries, 142, 208);
    else
        LCD.WriteAt(tries, 130, 208);

    LCD.WriteAt("/", 154, 208);
    LCD.WriteAt(maxTries, 166, 208);
}

void Grid::clearVect() {
    checkVect.clear();
}
