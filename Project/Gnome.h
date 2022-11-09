#ifndef Gnome_h
#define Gnome_h

#include "Moving.h"

class Gnome:public Moving{
    private:
        // dept = 1 αν έχει περπατήσει πάνω απο πετράδι
        int dept;
    public:
        Gnome();
        ~Gnome();
        int movement(int);
        int tracePotter(int,int,int,int);   
        friend class Engine;
};

#endif
