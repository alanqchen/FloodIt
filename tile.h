#ifndef TILE_H
#define TILE_H


class Tile {
public:
    Tile(); // Default constructor
    Tile(int Tcolor, int Trow, int Tcol); // Constuctor w/ params
    int getColor(); // Get tile color
    int getCol(); // Get tile column index [0,width-1]
    int getRow(); // Get tile row index [0,height-1]
    void setColor(int Tcolor); // Set tile color
    void setCol(int Tcol); // Set tile column index [0,width-1]
    void setRow(int Trow); // Set tile row index [0,height-1]
    bool wasChecked(); // Get tile check flag
    void setChecked(bool Tchecked); // Set tile check flag
private:
    int color; // Color of tile
    int row; // row index
    int col; // column index
    bool checked; // check flag
};

#endif // TILE_H
