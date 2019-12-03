#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "vectorlight.h"

class Scoreboard {
    public:
        Scoreboard(); // Constructor (no params)
        void print(); // Print scoreboard
        void printProfile(); // Print profile (footer)
        void newEntry(int score); // Add new entry to scoreboard
        int getMinScore(); // Get current min score on scoreboard
    private:
        char profile [6]; // Profile name (MUST BE <= 5 CHARACTERS)
        char names[5][6]; // Array of all names in scoreboard
        int scores[5]; // Array of all scores in scoreboard
        int minScore; // minimum score in scoreboard
};

#endif // SCOREBOARD_H
