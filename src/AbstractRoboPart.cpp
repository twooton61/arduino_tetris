#ifndef ABSTRACT_ROBO_PART_H
#define ABSTRACT_ROBO_PART_H

#include <AbstractRoboPart.h>
#include <RoboBrain.h>

class AbstractRoboPart {
    public:

    AbstractRoboPart(RoboBrain& robo_brain);

    virtual void setup() = 0;
};

AbstractRoboPart::AbstractRoboPart(RoboBrain& robo_brain){
    robo_brain.add_part(this);
}

#endif