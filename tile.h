#ifndef TILE_H
#define TILE_H


class Tile {
public:
    Tile();
    Tile(int Tcolor, int Trow, int Tcol);
    int getColor();
    int getCol();
    int getRow();
    void setColor(int Tcolor);
    void setRow(int Trow);
    void setCol(int Tcol);
    bool wasChecked();
    void setChecked(bool Tchecked);
private:
    int color;
    int row;
    int col;
    bool checked;
};

#endif // TILE_H
