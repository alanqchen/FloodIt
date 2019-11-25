#include "tile.h"

Tile::Tile() {}

Tile::Tile(int Tcolor, int Trow, int Tcol) {
    color = Tcolor;
    row = Trow;
    col = Tcol;
    checked = false;
}

int Tile::getRow() {
    return row;
}

int Tile::getCol() {
    return col;
}

int Tile::getColor() {
    return color;
}

bool Tile::wasChecked() {
    return checked;
}

void Tile::setRow(int Trow) {
    row = Trow;
}

void Tile::setCol(int Tcol) {
    col = Tcol;
}

void Tile::setColor(int Tcolor) {
    color = Tcolor;
}

void Tile::setChecked(bool Tchecked) {
    checked = Tchecked;
}
