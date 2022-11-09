#include "Engine.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>

#define STAR = 1


Engine::Engine(){
    playerName = new char[11];
}

void Engine::startGame(char** argv){
    Potter p;
    Gnome g;
    Traal e;
    HiScore h;
    fromFile(h,argv[2]);
    initscr();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);
    start_color();
    int choice;
    do{     
        choice = mainMenu();                 
        if(choice == 1){                     //Choice = 1 Play Game
            playerInit();                    //Choice = 2 HighScores
            monstersInit();                  //Choice = 3 Quit
            printMap(argv[1]);               
            setSpawns();
            int Result = startAction();
            printResult(Result);
            h << playerName << Points;
            toFile(h,argv[2]);
            clear();
            refresh();
        }else if(choice == 2){
            clear();
            h.showScores();
        }
    }while(choice!=3);
    clear();
    endwin();

}

void Engine::playerInit(){
    memset(playerName,0,sizeof(playerName)); 
    echo();
    curs_set(1);
    do{
        clear();
        refresh();
        move(5,2);
        printw("Enter Name (3-10 Characters): ");
        scanw("%s",playerName);
    }while((strlen(playerName)>10) || (strlen(playerName)<3));
    sumStars = 0;
    Points = 0;
    noecho();
    curs_set(0);
    clear();
    refresh();
}

void Engine::monstersInit(){
    g.dept = 0; // Dept = Περπάτησε πάνω απο πετράδι και πρέπει να το εκτυπώσει
    t.dept = 0;
    t.chase = 10; // Chase = Timer κυνηγητού
    t.pass = 0; // Pass = 1 = Chase mode
    t.lastMove = 0; // Ώστε να μην επιτρέπονται οι περιστροφές
}

int Engine::mainMenu(){
    int ch,res,done;
    done = 0;
    mvprintw(5,5,"Play Game");
    mvprintw(7,5,"Highscores");
    mvprintw(9,5,"Quit");
    mvaddch(5,15,'<');
    mvaddch(5,3,'>');
    do{
        ch = getch();
        switch (ch){
            case KEY_DOWN:
                if (mvinch(5,3) == '>'){
                    mvaddch(5,3,' ');
                    mvaddch(5,15,' ');
                    mvaddch(7,3,'>');
                    mvaddch(7,16,'<');
                }else if (mvinch(7,3) == '>'){
                    mvaddch(7,3,' ');
                    mvaddch(7,16,' ');
                    mvaddch(9,3,'>');
                    mvaddch(9,10,'<');
                }
                break;
            case KEY_UP:
                if(mvinch(7,3) == '>'){
                    mvaddch(7,3,' ');
                    mvaddch(7,16,' ');
                    mvaddch(5,3,'>');
                    mvaddch(5,15,'<');
                }else if (mvinch(9,3) == '>'){
                    mvaddch(9,3,' ');
                    mvaddch(9,10,' ');
                    mvaddch(7,3,'>');
                    mvaddch(7,16,'<');
                }
                break;
            case 10:    // 10 ASCII Value of Enter
                if(mvinch(5,3) == '>'){
                    res = 1; // Play
                    done = 1;
                }
                else if(mvinch(7,3) == '>'){
                    res = 2; // HighScores
                    done = 1;
                }
                else{
                    res = 3; // Quit
                    done = 1;
                }
                break;
        }
        refresh();
    }while(!done);
    return res;
}

void Engine::printMap(char* argv){
    std::ifstream file(argv,std::ios::in);
    if(!file) throw 4;
    char buffer[100];
    int ch;
    // keypad(stdscr,TRUE);
    // curs_set(0);
    dimY = -1;
    std::vector<char*> map;
    int sumStar = 0;
    int i=0;
    int turn = 1;
    while(!file.eof()){
        file.getline(buffer,99);
        map.push_back(buffer);
        if(turn == 1){
            dimX = strlen(buffer);
            turn = 2;
        }
        printw("%s\n",map[i]);
        dimY++;
        i++;
    }
    file.close();
}

void Engine::setSpawns(){
    
    std::srand((unsigned)std::time(NULL));
    int done = 0;
    do{
        p.posX = std::rand()%dimX;
        p.posY = std::rand()%dimY;
    }while(mvinch(p.posY,p.posX) != ' ');
    
    
    do{
        t.posX = std::rand()%dimX;
        t.posY = std::rand()%dimY;
    }while(((t.posX == p.posX) && (t.posY == p.posY)) ||
                (mvinch(t.posY,t.posX) != ' '));
    
    
    do{
        g.posX = std::rand()%dimX;
        g.posY = std::rand()%dimY;
    }while(((g.posX == p.posX) && (g.posY == p.posY)) ||
               ((g.posX == t.posX) && (g.posY == t.posY)) ||
                    mvinch(g.posY,g.posX) != ' ');
    
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    
    attron(COLOR_PAIR(2));
    move(g.posY,g.posX);
    addch(g.ID);
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(3));
    move(t.posY,t.posX);
    addch(t.ID);
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(4));
    move(p.posY,p.posX);
    addch(p.ID);
    attroff(COLOR_PAIR(4));

    int starPosX,starPosY;
        
    for(int i=0;i<10;i++){
        do{
            starPosX = std::rand()%dimX;
            starPosY = std::rand()%dimY;
        }while(mvinch(starPosY,starPosX) != ' ');
        move(starPosY,starPosX);
        attron(COLOR_PAIR(1));
        addch('s');
        attroff(COLOR_PAIR(1));
    }
}

int Engine::startAction(){
    int res;
    int ch;
    do{
        ch = getch();
        
        // Αν πατήσει Esc       // Res = 0 -> Άκυρη κίνηση (Wall)
        if (ch == 27){          // Res = 1 => Έγινε κίνηση 
            res = 4;            // Res = 2 => Lose
            break;              // Res = 3 => Victory    
        }                       // Res = 4 => Έγινε Quit    
                                    
        checkForGem(ch);
        res = p.movement(ch);
        
        // Αν νικήσει
        if (Points == 200){
            res = 3;
            break;
        }


        if(sumStars == 10)
            spawnScroll();
        if(res == 1){
            g.tracePotter(p.posX,p.posY,dimX,dimY);
            t.tracePotter(p.posX,p.posY,dimX,dimY);
        }
        if((p.posX == g.posX) && (p.posY == g.posY)){ // Ο Gnome πάτησε τον Potter
            attron(COLOR_PAIR(2));
            mvaddch(g.posY,g.posX,'G');
            attroff(COLOR_PAIR(2));
            res = 2;
        } 
        if((p.posX == t.posX) && (p.posY == t.posY)){ // O Traal πάτησε τον Potter
            attron(COLOR_PAIR(3));
            mvaddch(t.posY,t.posX,'T');
            attroff(COLOR_PAIR(3));
            res = 2;
        } 
    }while((res==1) || (res==0));

    return res;
}

void Engine::spawnScroll(){
    sumStars = 0;
    int scrollPosX, scrollPosY;
    do{
        scrollPosX = std::rand()%dimX;
        scrollPosY = std::rand()%dimY;
    }while(mvinch(scrollPosY,scrollPosX) != ' ');
    move(scrollPosY,scrollPosX);
    attron(COLOR_PAIR(1));
    addch('S');
    attroff(COLOR_PAIR(1));
}

void Engine::checkForGem(int ch){
    char castChar;
    switch(ch){
        case KEY_UP:
            castChar = mvinch(p.posY-1,p.posX) & A_CHARTEXT;
            break;
        
        case KEY_DOWN:
            castChar = mvinch(p.posY+1,p.posX) & A_CHARTEXT;
            break;
        
        case KEY_RIGHT:
            castChar = mvinch(p.posY,p.posX+1) & A_CHARTEXT;
            break;
        
        case KEY_LEFT:
            castChar = mvinch(p.posY,p.posX-1) & A_CHARTEXT;
            break;
    }
    if(castChar == 's'){
        Points+=10;
        sumStars++;
    }
    if(castChar == 'S'){
        Points+=100;
    }
}

void Engine::toFile(HiScore &h,char* file){
    std::ofstream fos(file,std::ios::out | std::ios::binary);
    if(!fos) throw 2;
    fos.write((char*)&h,sizeof(h));
    fos.close();
}

void Engine::fromFile(HiScore &h,char* file){
    std::ifstream fis(file,std::ios::in);
    if(!fis) throw 3;
    fis.read((char*)&h,sizeof(h));
    fis.close();
}

Engine::~Engine(){
    delete playerName;
}

void Engine::printResult(int Result){
    init_pair(6,COLOR_BLACK,COLOR_WHITE);
    attron(COLOR_PAIR(6));
    switch (Result){
        case 2: 
            mvprintw(9,19, "           ");
            mvprintw(10,19," Game Over ");
            mvprintw(11,19,"           ");
            break;
        case 3:
            mvprintw(9,19, "          ");
            mvprintw(10,19," You Won! ");
            mvprintw(11,19,"          ");
            break;
        case 4:
            mvprintw(9,19, "        ");
            mvprintw(10,19," Quited ");
            mvprintw(11,19,"        ");
            break;
    }
    mvprintw(13,10,"Press any key to continue...");
    refresh();
    attroff(COLOR_PAIR(6));
    getch();
    clear();
}