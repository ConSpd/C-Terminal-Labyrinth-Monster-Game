#include "Potter.h"
#include <ncurses.h>

Potter::Potter(){
    ID = 'P';
};

Potter::~Potter(){}

int Potter::movement(int ch){
    int oldPosY, oldPosX;
    oldPosY = posY;
    oldPosX = posX;
    
    // Αν είναι Space δεν κάνει τίποτα και φεύγει
    if(ch == ' ')
        return 1;

    move(posY,posX);
    addch(' ');

    switch(ch){
        case KEY_UP: movUp();break;
        case KEY_DOWN: movDown();break;
        case KEY_RIGHT: movRight();break;
        case KEY_LEFT: movLeft();break;
    }

    //start_color();
    attron(COLOR_PAIR(4));
    move(posY,posX);
    addch(ID);
    attroff(COLOR_PAIR(4));

    if((oldPosX != posX) || (oldPosY != posY))  // Έγινε κίνηση, είναι διαφορετικές οι νέες συντεταγμένες
        return 1;
    else if (ch == 27)  // Έκανε Quit
        return 4;  
    else
        return 0;   // Δεν έγινε σωστή κίνηση
    
}

