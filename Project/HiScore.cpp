#include "HiScore.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <ncurses.h>

void HiScore::operator<<(int newScore){
    int pos = -1;
    for(int i=0;i<5;i++){
        if(newScore > Score[i])
            pos = i;
    }
    
    if(pos > -1){
        for(int i=0;i<pos;i++){
            Score[i] = Score[i+1]; // Μεταφέρει τα stats μια θέση κάτω
            strcpy(Name[i],Name[i+1]);
        }
        Score[pos] = newScore;
        strcpy(Name[pos],tmpName);
    }
    memset(tmpName,0,sizeof(tmpName));
}

HiScore &HiScore::operator<<(char* newName){
    strcpy(tmpName,newName);
    return *this;
}

HiScore::HiScore(){
    for(int i=0;i<5;i++){
        strcpy(Name[i],"");
        Score[i] = 0;
    }
}

HiScore::~HiScore(){}

void HiScore::showScores(){
    clear();
    refresh();
    mvprintw(3,6,"Players");
    mvprintw(3,20,"Points");

    int y,x;
    y = 5;
    x = 6;
    move(y,x);
    for(int i=4;i>=0;i--)
        mvprintw(y++,x,"%-13s %d\n",Name[i],Score[i]);
    
    mvprintw(11,6,"Press any Key to exit...");
    getch();
    clear();
}
