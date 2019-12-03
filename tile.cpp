#include "tile.h"

// Default constructor
Tile::Tile() {}

// Constuctor w/ params
Tile::Tile(int Tcolor, int Trow, int Tcol) {
    color = Tcolor;
    row = Trow;
    col = Tcol;
    checked = false;
}

// Get tile row index [0,height-1]
int Tile::getRow() {
    return row;
}

// Get tile column index [0,width-1]
int Tile::getCol() {
    return col;
}

// Get tile color
int Tile::getColor() {
    return color;
}

// Get tile check flag
bool Tile::wasChecked() {
    return checked;
}

// Set tile row index [0,height-1]
void Tile::setRow(int Trow) {
    row = Trow;
}

// Set tile column index [0,width-1]
void Tile::setCol(int Tcol) {
    col = Tcol;
}

// Set tile color
void Tile::setColor(int Tcolor) {
    color = Tcolor;
}

// Set tile check flag
void Tile::setChecked(bool Tchecked) {
    checked = Tchecked;
}
