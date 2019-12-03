#include <FEHLCD.h>
#include <LCDColors.h>
#include <FEHUtility.h>
#include <FEHSD.h>
#include <string.h>
#include "vectorlight.cpp"
#include "vectorlight.h"
#include "scoreboard.h"

// Constructor (no params)
Scoreboard::Scoreboard() {
    // Open the scores file(don't overwrite). If it doesn't exist, create it
    FEHFile *fptr = SD.FOpen("SCORES.txt","a+");
    // Test if scores file was just opened
    if(SD.FEof(fptr)) {
        // Fill file w/ basic information
        // Set default profile to 'Guest'
        SD.FPrintf(fptr, "Guest\n");
        // Add empty scoreboard entries
        for(int i=0; i<5; i++)
            SD.FPrintf(fptr, "XXXXX\t%d\n", 0);
    }
    // Init temporary name variable
    char tempName [6];
    // Scan first line from file, this is the profile name
    SD.FScanf(fptr, "%s", profile);
    // Init temporary score variable
    int tempScore;
    // Loop through 5 entries
    for(int i=0; i<5; i++) {
        // Reach entry name and score and store in scoreboard arrays
        SD.FScanf(fptr, "%s%d", tempName, &tempScore);
        strcpy(names[i], tempName);
        scores[i] = tempScore;
    }
    // Find minimum score
    int min = scores[0];
    for(int i=1; i<5; i++) {
        if(scores[i] < min) {
            min = scores[i];
        }
    }
    // Set minScore to minimum score
    minScore= min;
    // Close file
    SD.FClose(fptr);
}

// Get current min score on scoreboard
int Scoreboard::getMinScore() {
    return minScore;
}

// Print scoreboard
void Scoreboard::print() {
    // Init touch variables for touch and release
    float x,y;
    // Clear screen
    LCD.Clear();
    // Set color to dark orange
    LCD.SetFontColor(DARKORANGE);
    // Print 'Scoreboard' in top-middle of screen
    LCD.WriteAt("Scoreboard",100,40);
    // Set color to black
    LCD.SetFontColor(FEHLCD::Black);
    // Draw dividing line
    LCD.DrawLine(5,70,314,70);
    // Print all names and their respective scores
    for(int i=0; i<5; i++) {
       LCD.WriteAt(names[i],98,90+22*i);
       LCD.WriteAt(scores[i],198,90+22*i);
    }
    // Print tap to exit prompt
    LCD.WriteAt("Tap to Exit",94,215);
    // Wait for touch and release
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
}

// Print profile (footer)
void Scoreboard::printProfile() {
    // Set color to gray
    LCD.SetFontColor(GRAY);
    // Print profile name on the bottom-middle of screen
    LCD.WriteAt(profile, 130, 213);
}

// Add new entry to scoreboard
void Scoreboard::newEntry(int score) {
    // Print scoreboard message w/ score
    LCD.WriteAt("Congrats!", 106, 20-10);
    LCD.WriteAt("You are in the top 5!", 34, 42-10);
    LCD.WriteAt("Score: ", 103, 64-10);
    LCD.WriteAt(score, 103+72+17, 64-10);
    // Print profile
    printProfile();
    // Create temporary names and scores array
    char namesTemp [5][6];
    int scoresTemp [5];
    // Init index tracker
    int index = 0;
    // Loop until score is larger than the score at
    // scores[index]
    while(score <= scores[index]) {
        // Copy name and score at index to temp arrays
        strcpy(namesTemp[index], names[index]);
        scoresTemp[index] = scores[index];
        index++; // Increment index
    }
    // Index is now at the position where the new score
    // should be inserted.
    // Copy profile name and new score into temp arrays
    strcpy(namesTemp[index], profile);
    scoresTemp[index] = score;
    // Init offset variable
    int offset;
    // If the new score is the highest, there is no offset
    if(index == 0) {
        offset = 0;
    // Otherwise, the new score is in the middle or at the end,
    // thus there needs to be a offset for the index in the old arrays
    } else {
        offset = 1;
    }
    index++; // Increment index
    // Copy old scoreboard data into new arrays until full
    while(index < 5) {
        strcpy(namesTemp[index], names[index-offset]);
        scoresTemp[index] = scores[index-offset];
        index++;
    }
    // Copy values in temp arrays back into the class arrays
    for(int i = 0; i < 5; i++) {
        strcpy(names[i], namesTemp[i]);
        scores[i] = scoresTemp[i];
    }
    // Open scores file and overwrite
    FEHFile *fptr = SD.FOpen("SCORES.txt","w");
    // Print profile name as first line
    SD.FPrintf(fptr, "%s\n", profile);
    // Add each new name and score to the file from the new scoreboard
    for(int i=0; i<5; i++) {
        SD.FPrintf(fptr, "%s\t%d\n", names[i], scores[i]);
    }
    // Find new min score in scoreboard
    int min = scores[0];
    for(int i=1; i<5; i++) {
        if(scores[i] < min) {
            min = scores[i];
        }
    }
    // Set the new min score
    minScore= min;
    // Close scores file
    SD.FClose(fptr);
    // Init touch variables for touch and release
    float x, y;
    // Print tap to continue prompt
    LCD.WriteAt("Tap to Continue",70,150);
    // Wait for touch and release
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    // Clear screen
    LCD.Clear(FEHLCD::White);
}

