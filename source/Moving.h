#ifndef Moving_h
#define Moving_h

#include <iostream>

class Moving{
    protected:
        int posX,posY;
        char ID;
    public:
        int showPos();
        void movUp();
        void movDown();
        void movRight();
        void movLeft();
        int getposX();
        int getposY();
        virtual int movement(int) = 0;
        Moving();
        ~Moving();
};

#endif