#ifndef Traal_h
#define Traal_h

#include "Moving.h"

class Traal:public Moving{
    private:
        int lastMove; // 1 Up, 2 Down, 3 Right, 4 Left
        int dept;
        int chase;  // Chase Timer
        int pass; // 1 Chase Mode, 0 Wander Mode
        int distance; // Απόσταση Traal απο Potter
    public:
        Traal();
        ~Traal();
        int onlyWay(int);
        int movement(int);
        int tracePotter(int,int,int,int);   
        friend class Engine;
};

#endif
