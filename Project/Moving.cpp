#include "Moving.h"

#include <iostream>
#include <ncurses.h>


void Moving::movUp(){
    if(mvinch(posY-1,posX) != '*')
        posY--;
}
void Moving::movDown(){
    if(mvinch(posY+1,posX) != '*')
        posY++;
}
void Moving::movRight(){
    if(mvinch(posY,posX+1) != '*')
        posX++;
}
void Moving::movLeft(){
    if(mvinch(posY,posX-1) != '*')
        posX--;
}
int Moving::getposX(){
    return posX;
}
int Moving::getposY(){
    return posY;
}

Moving::Moving(){}

Moving::~Moving(){}

