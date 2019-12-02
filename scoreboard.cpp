#include <FEHLCD.h>
#include <LCDColors.h>
#include <FEHUtility.h>
#include <FEHSD.h>
#include "scoreboard.h"


Scoreboard::Scoreboard() {
    for(int i=0; i<5; i++) {
        names.push_back("XXX");
        scores.push_back(0);
    }
}

void Scoreboard::print() {

    for(int i=0; i<5; i++) {
        LCD.WriteLine("%s\t%d", names.at(i), scores.at(i));
    }
}

void Scoreboard::newEntry() {
    char name[] = "jack";
    int score = 5;

    for(int i=4; i>=0; i--){
        if(score > scores.at(i)) {
            scores.insert(&scores.at(i), score);
            names.insert(&names.at(i), name);
        }
    }
}

