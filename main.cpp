#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <LCDColors.h>
#include <math.h>
#include "scoreboard.h"
#include "tile.h"
#include "grid.h"

// struct to store level parameters
struct gridSize_struct {
    int width; // num tiles wide
    int height; // num tiles tall
    int colors; // num colors
    int maxTries; // maximum tries
};

typedef struct gridSize_struct gridSize; // typedef struct to make life easier

// Helper function to calculate maximum tries/steps
int calcMaxTries(int rows, int cols, int colors, int level) {
    return (int)floor(25.0*((rows+cols)*colors)/((28.0)*6))+1+(int)(level/2.0);
}

// Helper function to fill grid level structs
void fillSize(gridSize* sizeArray, int index, int w, int h, int numC) {
    sizeArray[index].width = w;
    sizeArray[index].height = h;
    sizeArray[index].colors = numC;
    // Call function to calculate maximum tries and store result
    sizeArray[index].maxTries = calcMaxTries(h, w, numC, index);
}

// Main game loop function
int FloodIt(int width, int height, int numColors, int maxTries) {
    // Init touch variables
    float x = -1.0;
    float y = -1.0;
    // Trash touch variables for testing touch release
    float x_trash, y_trash;
    // Bool to store when the user finishes the grid
    bool complete = false;
    // Init grid using given parameters
    Grid grid(width, height, numColors, maxTries);

    // Keep printing grid and waiting for touch until grid is complete
    while(!complete) {
        // Print grid
        grid.print();
        // Wait for user touch within grid boundaries
        while(!LCD.Touch(&x, &y) && !((int)x > 70 && (int)x < 251 && (int)y > 25 && (int)y < 206));
        // Wait for release
        while(LCD.Touch(&x_trash, &y_trash));
        // Calculate row and col array indexes based on touch position
        int row = (((int)y-1 - 25) - (((int)y-1 - 25) % (180/height)))/(180/height);
        int col = (((int)x-1 - (160-(((180/height)*width)/2))) -
                   (((int)x-1 - (160-(((180/height)*width)/2))) % (180/height)))/(180/height);
        // Get color of the touched tile
        int touchColor = grid.getTile(row, col)->getColor();
        // Check if color is different than the top left tile's current color (don't do anything if the same)
        if(touchColor != grid.getTile(0, 0)->getColor()) {
            // Increment tries by 1
            grid.setTries(grid.getTries()+1);
            // Call the recursive update function to update the colors in grid
            grid.updateColors(grid.getTile(0, 0), grid.getTile(0, 0)->getColor(), touchColor);
            // Check if grid is complete
            complete = grid.isComplete();
        }
    }
    // Wait a bit to give the user the satisfaction of a completed grid
    Sleep(1.5);
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Return the user's number of tries/steps
    int result = grid.getTries();
    //grid.~Grid();
    return result;
}

// Prints score screen
void printScoreScreen(bool won, int level, int score, Scoreboard scoreboard) {
    // Init touch variable to detect when to continue
    float x, y;
    // Note: we don't need trash vars since we don't use x/y anyway
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Set text color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Check if the user lost on the level
    if(!won) {
        // Display failure text w/ score & level
        LCD.WriteAt("You Failed :(", 82, 30);
        LCD.WriteAt("Your final score was: ", 16, 57);
        LCD.WriteAt(score, 280, 57);
        LCD.WriteAt("You reached level ", 46, 84);
        LCD.WriteAt(level, 262, 84);
    // Check if user completed last level
    } else if(level == 11) {
        // Display win text w/ score
        LCD.SetFontColor(SCARLET);
        LCD.WriteAt("You Completed Every Level!", 4, 30);
        LCD.SetFontColor(FEHLCD::Black);
        LCD.WriteAt("Your final score was: ", 16, 57);
        LCD.WriteAt(score, 280, 57);
    // Check if user competed a level
    } else {
        // Display completion text w/ score & level
        LCD.WriteAt("You Completed Level ", 34, 30);
        LCD.WriteAt(level, 274, 30);
        LCD.WriteAt("Your current score is ", 16, 57);
        LCD.WriteAt(score, 280, 57);
    }
    // Print tap to continue prompt
    LCD.WriteAt("Tap to Continue",70,150);
    // Print current profile at bottom
    scoreboard.printProfile();
    // Wait for touch & release
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    // Clear screen
    LCD.Clear(FEHLCD::White);
}

// Prints help screen
void printHelp(Scoreboard scoreboard) {
    // Init touch variable to detect when to continue
    float x, y;
    // Note: we don't need trash vars since we don't use x/y anyway
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Set text color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Print help text
    LCD.WriteLine("The goal of the game is to fill the board with a single color.");
    LCD.WriteLine("Tap any color on the grid to change the top left tile's color, "
                  "and any adjacent matching tile color.");
    LCD.WriteLine("Completing Level - 5 points.");
    LCD.WriteLine("Extra steps - 1 point each.");
    LCD.WriteAt("Tap to Continue",70,150);
    // Print current profile at bottom
    scoreboard.printProfile();
    // Wait for touch & release
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
}

// Prints menu
void printMenu(Scoreboard scoreboard) {
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Init color list
    int colorList[10] = {SCARLET,DARKGREEN,DARKTURQUOISE,PURPLE,CHOCOLATE,GOLD,
                         KHAKI,LIGHTGREEN,LAWNGREEN,ORANGE};
    // Displays 'Flood-It!' with a random color from the color list for each character
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

    // Set color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Draw divider line
    LCD.DrawLine(5,91,314,91);
    // Set color to scarlet
    LCD.SetFontColor(SCARLET);
    // Create button rectangle for start
    LCD.FillRectangle(95,120,130,25);
    // Print 'Start' in the middle of the button
    LCD.WriteAt("Start", 125, 124);
    // Set color to dark orange
    LCD.SetFontColor(DARKORANGE);
    // Create button rectangle for scoreboard
    LCD.FillRectangle(95,165,130,25);
    // Print 'Scoreboard' in the middle of the button
    LCD.WriteAt("Scoreboard", 100, 169);
    // Print current profile at bottom
    scoreboard.printProfile();
    // Set color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Print simple help button at the botton right corner
    LCD.WriteAt("Help", 242, 193);
}

// Main menu-looping functionality
void startMenu() {
    // Init touch variables w/ their trash counterparts
    float x, y, x_trash, y_trash;
    // Init scoreboard (which calls constructor)
    Scoreboard scoreboard;
    // set player win flag to true
    bool player_won = true;

    // create grid levels array
    gridSize sizeArray [12];
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

    // Print main menu boxes and titles
    printMenu(scoreboard);
    while(true) {
        // Wait for user touch and release
        while(!LCD.Touch(&x, &y));
        while(LCD.Touch(&x_trash, &y_trash));

        // Check user touched start
        if(95 <= x && x <= 225 && 120 <= y && y <= 145) {
            // Clear the screen
            LCD.Clear(FEHLCD::White);
            // Reset player win flag to true
            player_won = true;
            // Set score to 0
            int score = 0;
            // Init tries variable
            int tries;
            // Set level array index to 0 (level 1)
            int level = 0;
            // Keep playing levels until the player losses or reaches the end
            while(player_won && level < 12) {
                // Call the main game function, passing the current level
                //   parameters and storing the returned number of tries to complete
                tries = FloodIt(sizeArray[level].width, sizeArray[level].height,
                                sizeArray[level].colors, sizeArray[level].maxTries);
                // Check if tries is equal to or under to max tries
                //   (check if player won the level)
                if(tries <= sizeArray[level].maxTries) {
                    // Set win flag to true
                    player_won = true;
                    // Increment score by 5 for completing level
                    score += 5;
                    // Increment score by the number of tries left over
                    score += sizeArray[level].maxTries-tries;
                // Otherwise, plater lost
                } else {
                    // Set win flag to false;
                    player_won = false;
                }
                // Increment level number
                level++;
                // Print score screen passing in post-level stats
                printScoreScreen(player_won, level, score, scoreboard);
            }
            // Game has ended
            // Check if player's score will be in the scoreboard
            if(score > scoreboard.getMinScore()) {
                // Enter score into scoreboard
                scoreboard.newEntry(score);
            }
            // Print main menu
            printMenu(scoreboard);
            continue;
        // Check if user tapped scoreboard
        } else if(95 <= x && x <= 225 && 165 <= y && y <= 190) {
            // Print scoreboard
            scoreboard.print();
            // Print main menu
            printMenu(scoreboard);
            continue;
        // Check if user tapped help
        } else if(x >= 242 && y >= 193) {
            // Print help screen
            printHelp(scoreboard);
            // Print main menu
            printMenu(scoreboard);
            continue;
        }
    }
}

int main(void) {
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Set font color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Print version
    LCD.WriteLine("Flood It! v1.3.1");
    // Print credits
    LCD.WriteLine("Made by Alan Chen & Jeff Bonner");
    // Wait 3 seconds
    Sleep(3.0);
    // Set random seed
    srand(TimeNow());
    // Clear screen
    LCD.Clear(FEHLCD::White);
    // Go to start menu
    //FloodIt(9, 6, 7, 100);
    startMenu();

    return 0;
}
