#ifndef HiScore_h
#define HiScore_h
#include <iostream>
#include <vector>
#include <string>
class HiScore{
    private:
        char tmpName[11];
        char Name[5][11];
        int Score[5];
    public:
        void operator<<(int);
        void showScores();
        HiScore& operator<<(char*);
        HiScore();
        ~HiScore();

};

#endif