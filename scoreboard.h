#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "vectorlight.h"

class Scoreboard {
    public:
        Scoreboard();
        void print();
        void newEntry(char []);
    private:
        VectorLight <char*> names;
        VectorLight <int> scores;
};

#endif // SCOREBOARD_H
