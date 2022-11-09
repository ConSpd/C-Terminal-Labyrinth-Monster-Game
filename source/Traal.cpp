#include "Traal.h"
#include <ncurses.h>
#include <cmath>
#include <iostream>

Traal::Traal(){
    ID = 'T';
}

Traal::~Traal(){}

int Traal::movement(int ch){
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

    attron(COLOR_PAIR(3));
    move(posY,posX);
    addch('T');
    attroff(COLOR_PAIR(3));    
    return 0;
}

int Traal::tracePotter(int PotterX,int PotterY,int dimX,int dimY){
    // Αν ο Potter βρεθεί στο ίδιο κουτάκι με το Traal το Traal δεν θα κουνηθεί
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

    distance = std::abs(PotterX - posX) + std::abs(PotterY - posY);
    // 0 Απόσταση για το τετραγωνάκι του Potter
    
    

    if(( distance <= 7) && (chase > 0))
        pass = 1; // Αν βρίσκεται 7 blocks απο τον Potter αρχίζει και τον κυνηγάει για 8 γύρους
    
    
    if(pass){
        arr[PotterY][PotterX] = 0;  
    }else{
        if((PotterY-4) > 0)
            arr[PotterY-4][PotterX] = 0;
        else if((PotterX-4) > 0)
            arr[PotterY][PotterX-4] = 0; // Θέτουμε ως 0 το σημείο που κυνηγάει το τέρας
        else if((PotterY+4) < dimY)
            arr[PotterY+4][PotterX] = 0;
        else
            arr[PotterY][PotterX+4] = 0;
    }
    
    // Θέτουμε 999 στο τετραγωνάκι του Gnome ώστε να το αναγνωρίσουμε όταν το βρούμε
    arr[posY][posX] = 999;
        
    int x,y;
    x = y = 1;
    int weight = 0;
    int done = 0;
    int moved = 0;
    
    do{
        for(int i=1;i<dimY-1;i++){ // Πρώτη γύρα ψάχνει για 0, Δεύτερη για 1, Τρίτη για 2
           for(int j=1;j<dimX-1;j++){
                
                if(arr[i][j] ==  weight){ // Εδώ βρισκόμαστε στο τετραγωνάκι του P στον πρώτο γύρο
                    
                        if(mvinch(i-y,j) != '*'){
                            if(arr[i-y][j] == 999){
                                if((lastMove!=1) || onlyWay(2)){ // To only way χρησιμοποιείται για να επιτρέψει το 180 εάν έχει εγκλωβιστεί
                                    movement(2);
                                    lastMove = 2;
                                    done = 1;
                                    moved = 1;
                                }
                            }
                            else if (arr[i-y][j] == -1)
                                arr[i-y][j] = weight+1;
                        }


                        if(mvinch(i+y,j) != '*'){
                            if(arr[i+y][j] == 999){
                                if((lastMove!=2) || onlyWay(1)){
                                    movement(1);
                                    lastMove = 1;
                                    done = 1;
                                    moved = 1;
                                }
                            }
                            else if (arr[i+y][j] == -1)
                                arr[i+y][j] = weight+1;
                        }

                    if(moved == 1) break; 

                        if(mvinch(i,j+x) != '*'){
                            if(arr[i][j+x] == 999){ // Εδώ βρίσκουμε το Gnome
                                if((lastMove!=3) || onlyWay(4)){
                                    movement(4);
                                    lastMove = 4;
                                    moved = 1;
                                    done = 1;
                                }
                            }else if(arr[i][j+x] == -1)
                                arr[i][j+x] = weight+1;
                        }

                    if(moved == 1) break;
                    
                        if(mvinch(i,j-x) != '*'){
                            if(arr[i][j-x] == 999){
                                if((lastMove!=4) || onlyWay(3)){
                                    movement(3);
                                    lastMove = 3;
                                    done = 1;
                                    moved = 1;
                                }
                            }
                            else if (arr[i][j-x] == -1)
                                arr[i][j-x] = weight+1;
                        }

                    if(moved == 1) break;

                                       
                }

            if(moved == 1) break;

           }
           
        }
    
        weight++;
        moved = 0;
    }while(!done);

    // Aν είναι σε Chase Mode
    if(pass)
        chase--;
    
    // Ώστε να σταματήσει το chase
    if(chase == 0)
        pass = 0; 

    // Μειώνεται έτσι ώστε να κάνει wandering και στο -20 να κάνει reset
    if(chase <=0 )
        chase--;
    
    // Reset περνάει 10 γύρους κυνηγώντας και 20 wandering
    if(chase == -20)
        chase = 10;  
    
    for(int i=0;i<dimY;i++)
        delete[] arr[i];
    delete[] arr;
    
    return 0;
}

int Traal::onlyWay(int direc){
    int theWay = 0;
    switch(direc){
        case 1: // Up
            if((mvinch(posY+1,posX) == '*') && 
                    (mvinch(posY,posX+1) == '*') &&
                        (mvinch(posY,posX-1) == '*'))
                theWay = 1;
        break;
        
        case 2: // Down
        if((mvinch(posY-1,posX) == '*') && 
                (mvinch(posY,posX+1) == '*') &&
                    (mvinch(posY,posX-1) == '*'))
            theWay = 1;
        break;
        
        case 3: // Right
            if((mvinch(posY+1,posX) == '*') && 
                    (mvinch(posY-1,posX) == '*') &&
                        (mvinch(posY,posX-1) == '*'))
                theWay = 1;
        break;
        
        case 4: // Left
            if((mvinch(posY+1,posX) == '*') && 
                    (mvinch(posY-1,posX) == '*') &&
                        (mvinch(posY,posX+1) == '*'))
                theWay = 1;
         break;
    }
    return theWay;
}
