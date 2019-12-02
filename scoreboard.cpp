#include <FEHLCD.h>
#include <LCDColors.h>
#include <FEHUtility.h>
#include <FEHSD.h>
#include "vectorlight.cpp"
#include "vectorlight.h"
#include "scoreboard.h"


Scoreboard::Scoreboard() {
    for(int i=0; i<5; i++) {
        names.push_back("XXX");
        scores.push_back(0);
    }
}

void Scoreboard::print() {
    float x,y;
    LCD.Clear();
    for(int i=0; i<5; i++) {
        LCD.WriteAt(names.at(i), 140, 10+(17*i));
        LCD.WriteAt(scores.at(i), 200, 10+(17*i));
    }
    while(!LCD.Touch(&x, &y));
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

