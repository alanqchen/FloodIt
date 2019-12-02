#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard {
    public:
        Scoreboard();
        void print();
        void newEntry(char []);
    private:
        char top5names[5][3];
        int top5scores[5];
};

#endif // SCOREBOARD_H
