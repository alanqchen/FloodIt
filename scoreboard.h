#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "vectorlight.h"

class Scoreboard {
    public:
        Scoreboard();
        void print();
        void printProfile();
        void newEntry(int score);
        int getMinScore();
        char* getProfile();
    private:
        void printKeyboard();
        char profile [6];
        char names[5][6];
        int scores[5];
        int minScore;
};

#endif // SCOREBOARD_H
