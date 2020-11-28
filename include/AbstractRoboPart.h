#ifndef ABSTRACT_ROBO_PART_H
#define ABSTRACT_ROBO_PART_H

class RoboBrain;

class AbstractRoboPart {
    public:

    AbstractRoboPart(RoboBrain& robo_brain);

    virtual void setup() = 0;
};

#endif