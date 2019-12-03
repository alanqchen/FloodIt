#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <LCDColors.h>
#include <math.h>
#include "scoreboard.h"
#include "tile.h"
#include "grid.h"

struct gridSize_struct {
    int width;
    int height;
    int colors;
    int maxTries;
};

typedef struct gridSize_struct gridSize;

int calcMaxTries(int rows, int cols, int colors, int level) {
    return (int)floor(25.0*((rows+cols)*colors)/((28.0)*6))+1+(int)(level/2.5);
}

// Helper function
void fillSize(gridSize* sizeArray, int index, int w, int h, int numC) {
    sizeArray[index].width = w;
    sizeArray[index].height = h;
    sizeArray[index].colors = numC;
    sizeArray[index].maxTries = calcMaxTries(h, w, numC, index);
}

int FloodIt(int width, int height, int numColors, int maxTries) {
    float x = -1.0;
    float y = -1.0;
    float x_trash, y_trash;
    int row;
    int col;
    bool complete = false;

    Grid grid(width, height, numColors, maxTries);
    while(!complete) {
        // Print grid
        grid.print();
        // Wait for user touch
        while(!LCD.Touch(&x, &y) && !((int)x > 70 && (int)x < 251 && (int)y > 25 && (int)y < 206));
        while(LCD.Touch(&x_trash, &y_trash));
        int row =(((int)y-1 - 25) - (((int)y-1 - 25) % (180/height)))/(180/height); // This may go wrong
        int col = (((int)x-1 - (160-(((180/height)*width)/2))) - (((int)x-1 - (160-(((180/height)*width)/2))) % (180/height)))/(180/height);
        //LCD.WriteLine(row);
        //LCD.WriteLine(col);
        int touchColor = grid.getTile(row, col)->getColor();
        //LCD.WriteLine(touchColor);
        if(touchColor != grid.getTile(0, 0)->getColor()) { // Check if color is different
            grid.setTries(grid.getTries()+1);
            grid.updateColors(grid.getTile(0, 0), grid.getTile(0, 0)->getColor(), touchColor);
            complete = grid.isComplete();
        }
    }
    Sleep(1.5);
    LCD.Clear(FEHLCD::White);
    /*
    if(grid.getTries() <= grid.getMaxTries())
        LCD.WriteLine("YOU WON!");
    else
        LCD.WriteLine("You Failed :(");
    */
    return grid.getTries();
}

void printScoreScreen(bool won, int level, int score, Scoreboard scoreboard) {
    float x, y;
    LCD.Clear(FEHLCD::White);
    LCD.SetFontColor(FEHLCD::Black);
    if(!won) {
        LCD.WriteAt("You Failed :(", 82, 30);
        LCD.WriteAt("Your final score was: ", 16, 57);
        LCD.WriteAt(score, 280, 57);
        LCD.WriteAt("You reached level ", 46, 84);
        LCD.WriteAt(level, 262, 84);
    } else if(level == 11) {
        LCD.SetFontColor(SCARLET);
        LCD.WriteAt("You Completed Every Level!", 4, 30);
        LCD.SetFontColor(FEHLCD::Black);
        LCD.WriteAt("Your final score was: ", 16, 57);
        LCD.WriteAt(score, 280, 57);
    } else {
        LCD.WriteAt("You Completed Level ", 34, 30);
        LCD.WriteAt(level, 274, 30);
        LCD.WriteAt("Your current score is ", 16, 57);
        LCD.WriteAt(score, 280, 57);
    }
    LCD.WriteAt("Tap to Continue",70,150);
    scoreboard.printProfile();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    LCD.Clear(FEHLCD::White);
}

void printHelp(Scoreboard scoreboard) {
    float x, y;
    LCD.Clear(FEHLCD::White);
    LCD.SetFontColor(FEHLCD::Black);
    LCD.WriteLine("The goal of the game is to fill the board with a single color.");
    LCD.WriteLine("Tap any color on the grid to change the top left tile's color, and any adjacent matching tile color.");
    LCD.WriteLine("Completing Level - 5 points.");
    LCD.WriteLine("Extra steps - 1 point each.");
    LCD.WriteAt("Tap to Continue",70,150);
    scoreboard.printProfile();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    //LCD.Clear(FEHLCD::White);
}

void printMenu(Scoreboard scoreboard) {
    LCD.Clear(FEHLCD::White);
    int colorList[10] = {SCARLET,DARKGREEN,DARKTURQUOISE,PURPLE,CHOCOLATE,GOLD,KHAKI,LIGHTGREEN,LAWNGREEN,ORANGE};
    int colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("F", 106, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("l", 106+12, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("o", 106+12*2, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("o", 106+12*3, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("d", 106+12*4, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("-", 106+12*5, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("I", 106+12*6, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("t", 106+12*7, 60);
    colorIndex = rand() % 10;
    LCD.SetFontColor(colorList[colorIndex]);
    LCD.WriteAt("!", 106+12*8, 60);
    LCD.SetFontColor(FEHLCD::Black);
    LCD.DrawLine(5,91,314,91);
    LCD.SetFontColor(SCARLET);
    LCD.FillRectangle(95,120,130,25);
    //LCD.SetFontColor(WHITE);
    LCD.WriteAt("Start", 125, 124);
    LCD.SetFontColor(DARKORANGE);
    LCD.FillRectangle(95,165,130,25);
    LCD.WriteAt("Scoreboard", 100, 169);
    scoreboard.printProfile();
    LCD.SetFontColor(FEHLCD::Black);
    LCD.WriteAt("Help", 242, 193);
}

void startMenu() {
    Sleep(1.0);

    //int grid_size = 5, colors = 4;
    float x, y, x_trash, y_trash;
    Scoreboard scoreboard;
    bool player_won = true;

    // create grid
    gridSize sizeArray [20];
    // LEVEL 1
    fillSize(sizeArray, 0, 3, 2, 3);
    // LEVEL 2
    fillSize(sizeArray, 1, 3, 3, 3);
    // LEVEL 3
    fillSize(sizeArray, 2, 4, 3, 3);
    // LEVEL 4
    fillSize(sizeArray, 3, 4, 4, 4);
    // LEVEL 5
    fillSize(sizeArray, 4, 5, 4, 4);
    // LEVEL 6
    fillSize(sizeArray, 5, 6, 4, 4);
    // LEVEL 7
    fillSize(sizeArray, 6, 7, 5, 4);
    // LEVEL 8
    fillSize(sizeArray, 7, 7, 6, 5);
    // LEVEL 9
    fillSize(sizeArray, 8, 8, 6, 5);
    // LEVEL 10
    fillSize(sizeArray, 9, 9, 6, 6);
    // LEVEL 11
    fillSize(sizeArray, 10, 10, 7, 7);
    // LEVEL 12
    fillSize(sizeArray, 11, 12, 8, 7);

    //write main menu boxes and titles
    /*
    LCD.Clear( FEHLCD::White );
    LCD.SetFontColor(FEHLCD::Black);
    LCD.WriteAt("FloodIt!", 94,120);
    LCD.WriteAt("Start", 94,140);
    LCD.WriteAt("Scoreboard", 94,170);
    */
    printMenu(scoreboard);
    while(true) {
        // Wait for user touch and release
        while(!LCD.Touch(&x, &y));
        while(LCD.Touch(&x_trash, &y_trash));

        // if user clicks start
        if(95 <= x && x <= 225 && 145 >= y && y >= 120) {
            LCD.Clear(FEHLCD::White);
            player_won = true;
            int score = 0;
            int tries;
            //int maxTries = 18;
            int level = 0;
            while(player_won && level < 12) {
                tries = FloodIt(sizeArray[level].width, sizeArray[level].height, sizeArray[level].colors, sizeArray[level].maxTries);
                if(tries <= sizeArray[level].maxTries) {
                    player_won = true;
                    score += 5;
                    score += sizeArray[level].maxTries-tries;
                } else
                    player_won = false;
                level++;
                printScoreScreen(player_won, level, score, scoreboard);
            }
            if(score > scoreboard.getMinScore())
                scoreboard.newEntry(score);
            /*
            LCD.Clear( FEHLCD::White);
            LCD.WriteAt("FloodIt!", 94,120);
            LCD.WriteAt("Start", 94,140);
            LCD.WriteAt("Scoreboard", 94,170);
            */
            printMenu(scoreboard);
            //while(!LCD.Touch(&x, &y));
            continue;
        } else if(95 <= x && x <= 225 && 165 <= y && y <= 190) //if user clicks scoreboard
        {
            scoreboard.print();
            printMenu(scoreboard);
            //while(!LCD.Touch(&x, &y));
            continue;
        } else if(x >= 242 && y >= 193) {
            printHelp(scoreboard);
            printMenu(scoreboard);
            continue;
        }
    }
}

int main(void)
{
    LCD.Clear(FEHLCD::White);
    LCD.SetFontColor(FEHLCD::Black);
    LCD.WriteLine("Flood It! v1.3.1");
    Sleep(3.0);
    srand(TimeNow());
    // Display menu

    float x,y, x_trash, y_trash;
    bool quit = false;

    LCD.Clear(FEHLCD::White);
    LCD.SetFontColor(FEHLCD::White);
    startMenu();
    /*
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
            //FloodIt(4, 4, 4);
        }
    }
    */
    return 0;
}
