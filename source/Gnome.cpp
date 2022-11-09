#include "Gnome.h"
#include <ncurses.h>
#include <iostream>

Gnome::Gnome(){
    ID = 'G';
}

Gnome::~Gnome(){}

int Gnome::movement(int ch){
    move(posY,posX);
    if(dept == 1){
        start_color();
        attron(COLOR_PAIR(1));
        addch('s');
        attroff(COLOR_PAIR(1));
        dept = 0;
    }else if(dept == 2){
        attron(COLOR_PAIR(1));
        addch('S');
        attroff(COLOR_PAIR(1));
        dept = 0;
    }else
        addch(' ');
    
    switch(ch){
        case 1: movUp();break;
        case 2: movDown();break;
        case 3: movRight();break;
        case 4: movLeft();break;
    }
    char castChar = mvinch(posY,posX) & A_CHARTEXT;
    if (castChar == 's')
        dept = 1;
    else if (castChar == 'S')
        dept = 2;

    attron(COLOR_PAIR(2));
    move(posY,posX);
    addch('G');
    attroff(COLOR_PAIR(2));    
    return 0;
};



int Gnome::tracePotter(int PotterX,int PotterY,int dimX,int dimY){
    
    // Αν ο Potter βρεθεί στο ίδιο κουτάκι με το Gnome το Gnome δεν θα κουνηθεί
    if((PotterY == posY) && (PotterX == posX)) 
        return 0;

    int **arr = new int*[dimY];
    for(int i=0;i<dimY;i++)
        arr[i] = new int[dimX];
    
    // Αρχικοποιούμε παντού με -1 ώστε να ελέγξουμε τον πίνακα μετά για μη επεξεργασμένα blocks
    for(int i=0;i<dimY;i++){
        for(int j=0;j<dimX;j++)
            arr[i][j] = -1;
    }

    // 0 Απόσταση για το τετραγωνάκι του Potter
    arr[PotterY][PotterX] = 0;
    // Θέτουμε 999 στο τετραγωνάκι του Gnome ώστε να το αναγνωρίσουμε όταν το βρούμε
    arr[posY][posX] = 999;
        
    int x,y;
    x = y = 1;
    int weight = 0;
    int done = 0;
    int moved = 0;
    
    do{
        for(int i=1;i<dimY-1;i++){
           for(int j=1;j<dimX-1;j++){
                
                if(arr[i][j] ==  weight){ // Εδώ βρισκόμαστε στο τετραγωνάκι του P στον πρώτο γύρο
                    
                    
                    if(mvinch(i,j+x) != '*'){
                        if(arr[i][j+x] == 999){ // Εδώ βρίσκουμε το Gnome
                            movement(4);
                            moved = 1;
                            done = 1;
                        }else if(arr[i][j+x] == -1)
                            arr[i][j+x] = weight+1;
                    }

                    if(moved == 1) break;
                    
                    if(mvinch(i,j-x) != '*'){
                        if(arr[i][j-x] == 999){
                            movement(3);
                            done = 1;
                            moved = 1;
                        }
                        else if (arr[i][j-x] == -1)
                            arr[i][j-x] = weight+1;
                    }

                    if(moved == 1) break;

                    if(mvinch(i+y,j) != '*'){
                        if(arr[i+y][j] == 999){
                            movement(1);
                            done = 1;
                            moved = 1;
                        }
                        else if (arr[i+y][j] == -1)
                            arr[i+y][j] = weight+1;
                    }

                    if(moved == 1) break;                    
                    
                    if(mvinch(i-y,j) != '*'){
                        if(arr[i-y][j] == 999){
                            movement(2);
                            done = 1;
                            moved = 1;
                        }
                        else if (arr[i-y][j] == -1)
                            arr[i-y][j] = weight+1;
                    }

                    if(moved == 1) break;                    
                }

            if(moved == 1) break;

           }
           
        }
        weight++;
        moved = 0;
    }while(!done);
    
    for(int i=0;i<dimY;i++)
        delete[] arr[i];
    delete[] arr;
    return 0;
}
    
    




