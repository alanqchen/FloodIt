#include <FEHLCD.h>
#include <LCDColors.h>
#include <FEHUtility.h>
#include <FEHSD.h>
#include <string.h>
#include "vectorlight.cpp"
#include "vectorlight.h"
#include "scoreboard.h"


Scoreboard::Scoreboard() {
    FEHFile *fptr = SD.FOpen("SCORES.txt","a+");
    if(SD.FEof(fptr)) {
        LCD.WriteLine("File doesn't exist, filling");
        SD.FPrintf(fptr, "Guest\n");
        for(int i=0; i<5; i++)
            SD.FPrintf(fptr, "XXXXX\t%d\n", 0);
    }
    char tempName [6];
    SD.FScanf(fptr, "%s", profile);
    int tempScore;
    for(int i=0; i<5; i++) {
        SD.FScanf(fptr, "%s%d", tempName, &tempScore);
        strcpy(names[i], tempName);
        scores[i] = tempScore;
    }
    int min = scores[0];
    for(int i=1; i<5; i++) {
        if(scores[i] < min) {
            min = scores[i];
        }
    }
    minScore= min;
    SD.FClose(fptr);
}

int Scoreboard::getMinScore() {
    return minScore;
}

void Scoreboard::print() {
    float x,y;
    LCD.Clear();
    LCD.SetFontColor(DARKORANGE);
    LCD.WriteAt("Scoreboard",100,40);
    LCD.SetFontColor(FEHLCD::Black);
    LCD.DrawLine(5,70,314,70);
    for(int i=0; i<5; i++) {
       LCD.WriteAt(names[i],98,90+22*i);
       LCD.WriteAt(scores[i],198,90+22*i);
    }
    LCD.WriteAt("Tap to Exit",94,215);
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
}

void Scoreboard::printProfile() {
    LCD.SetFontColor(GRAY);
    LCD.WriteAt(profile, 130, 213);
}

void Scoreboard::newEntry(int score) {

    LCD.WriteAt("Congrats!", 106, 20-10);
    LCD.WriteAt("You are in the top 5!", 34, 42-10);
    LCD.WriteAt("Score: ", 103, 64-10);
    LCD.WriteAt(score, 103+72+17, 64-10);
    printProfile();
    char namesTemp [5][6];
    int scoresTemp [5];
    int index = 0;
    while(score <= scores[index]) {
        strcpy(namesTemp[index], names[index]);
        scoresTemp[index] = scores[index];
        index++;
    }
    strcpy(namesTemp[index], profile);
    scoresTemp[index] = score;
    int offset;
    if(index == 0) {
        offset = 0;
    } else {
        offset = 1;
    }
    index++;
    while(index < 5) {
        strcpy(namesTemp[index], names[index-offset]);
        scoresTemp[index] = scores[index-offset];
        index++;
    }
    for(int i = 0; i < 5; i++) {
        strcpy(names[i], namesTemp[i]);
        scores[i] = scoresTemp[i];
    }
    FEHFile *fptr = SD.FOpen("SCORES.txt","w");
    SD.FPrintf(fptr, "%s\n", profile);
    for(int i=0; i<5; i++) {
        SD.FPrintf(fptr, "%s\t%d\n", names[i], scores[i]);
    }
    int min = scores[0];
    for(int i=1; i<5; i++) {
        if(scores[i] < min) {
            min = scores[i];
        }
    }
    minScore= min;
    SD.FClose(fptr);
    float x, y;
    LCD.WriteAt("Tap to Continue",70,150);
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    LCD.Clear(FEHLCD::White);
}

