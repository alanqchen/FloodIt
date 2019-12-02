#include <FEHLCD.h>
#include <LCDColors.h>
#include <FEHUtility.h>
#include <FEHSD.h>
#include "scoreboard.h"


Scoreboard::Scoreboard() {
    FEHFile *fptr = SD.FOpen("scores.txt", "w+");
    for(int i=0; i<5; i++) {
        strcpy(top5names[i], "XXX");
        top5scores[i] = 0;
        SD.FPrintf(fptr, "%s %i", top5names[i], top5scores[i]);
    }
    //Close file
    SD.FClose(fptr);
}

void Scoreboard::print() {
    for(int i=0; i<5; i++) {
        LCD.WriteLine("%s\t%d", top5names[i], top5scores[i]);
    }
}

void Scoreboard::newEntry(char initials[]) {


}
