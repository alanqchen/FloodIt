#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include "tile.h"
#include "grid.h"


int FloodIt(int width, int numColors) {
    float x = -1.0;
    float y = -1.0;
    int row;
    int col;
    bool complete = false;
    // create grid
    Grid grid(width, numColors, 18);
    while(!complete) {
        // Print grid
        grid.print();
        // Wait for user touch
        while(!LCD.Touch(&x, &y) && !((int)x > 70 && (int)x < 251 && (int)y > 25 && (int)y < 206));
        int row =(((int)y-1 - 25) - (((int)y-1 - 25) % (180/width)))/(180/width); // This may go wrong
        int col = (((int)x-1 - 70) - (((int)x-1 - 70) % (180/width)))/(180/width);
        //LCD.WriteLine(row);
        //LCD.WriteLine(col);
        int touchColor = grid.getTile(row, col)->getColor();
        LCD.WriteLine(touchColor);
        if(touchColor != grid.getTile(0, 0)->getColor()) { // Check if color is different
            grid.setTries(grid.getTries()+1);
            grid.updateColors(grid.getTile(0, 0), grid.getTile(0, 0)->getColor(), touchColor);
            complete = grid.isComplete();
        }
    }
    LCD.WriteLine("YOU WIN!");
    Sleep(5.0);
    LCD.Clear(FEHLCD::White);
}

int main(void)
{
    LCD.WriteLine( "Flood It! v1.1.0" );
    Sleep(3.0);
    srand(TimeNow());
    // Display menu

    float x,y, x_trash, y_trash;
    bool quit = false;
    // This is a test commit

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    while(quit != true) {
        LCD.WriteLine("Touch anywhere to play one game");
        // Wait for user touch
        while(!LCD.Touch(&x, &y));
        // This will be a if-else ladder to determine selection
        if(0 < x & 0 < y) {
            LCD.WriteLine( "Choosen play one round game" );
            Sleep(2.0);
            LCD.Clear(FEHLCD::White);
            // Have color number/grid size/num steps selection in the future
            FloodIt(9, 4);
        }
    }
    return 0;
}
