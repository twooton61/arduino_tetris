#ifndef ABSTRACT_ROBO_PART_H
#define ABSTRACT_ROBO_PART_H

#include <RoboBrain.h>

class AbstractRoboPart {
    public:

    AbstractRoboPart(){
    }

    virtual void setup() = 0;
};

#endif