#ifndef Potter_h
#define Potter_h

#include "Moving.h"

class Potter:public Moving{
    public:
        Potter();
        ~Potter();
        int movement(int);
        friend class Engine;
};


#endif