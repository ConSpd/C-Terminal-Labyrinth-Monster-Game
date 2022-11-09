#ifndef Engine_h
#define Engine_h

#include "Gnome.h"
#include "Potter.h"
#include "Traal.h"
#include "HiScore.h"
#include <string>


class Engine{
    private:
        int dimX,dimY;
        char* playerName;
        int sumStars;
        int Points;
        Potter p;
        Traal t;
        Gnome g;
    
    public:
        Engine();
        ~Engine();
        void setSpawns(); // Αρχικοποιεί τις τυχαίες θέσεις του Potter και των τεράτων.
        void startGame(char**); // Κύρια μέθοδος που καλείται απο την main.
        void printMap(char*);
        int startAction();
        void spawnScroll(); // Δημιουργεί σε τυχαία θέση τον Πάπυρο
        void checkForGem(int); // Ελέγχει για πετράδι ώστε να προσθέσει πόντους στον Potter
        int mainMenu();
        void playerInit(); // Θέτει τις κατάλληλες αρχικοποιήσεις για τα attributes του παίχτη.
        void printResult(int); // Win, Lose , Quit
        void toFile(HiScore&,char*); // Write to File
        void fromFile(HiScore&,char*); // Read from File
        void monstersInit(); // Θέτει τις κατάλληλες αρχικοποιήσεις για τα τέρατα.

        friend class Potter;
        friend class Traal;
        friend class Gnome;
};


#endif
