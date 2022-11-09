#include "Engine.h"
#include "HiScore.h"
#include <iostream>
#include <ncurses.h>

int main(int argc,char** argv){
    try{
        if(argc<3) throw "Too few arguments";
        Engine e;
        e.startGame(argv);
    }
    catch(const char* msg){
        std::cerr << "Error " << msg << ": ";
        if(!argv[1]){
            std::cerr << "missing Map & Highscore Files" << std::endl;
        }else{
            std::cerr << "missing Highscore File" << std::endl;
        }
        exit(1);
    }catch(int e){
        endwin();
        std::cerr << "Error " << e << ": ";
        if (e == 2)
            std::cout << "Writing to Highscore File" << std::endl;
        else if(e == 3)
            std::cout << "Reading Highscore File" << std::endl;
        else if(e == 4)
            std::cout << "Map file does not exist" << std::endl;
    }
    return 0;    
}