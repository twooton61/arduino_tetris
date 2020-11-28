#ifndef ABSTRACT_ROBO_PART_H
#define ABSTRACT_ROBO_PART_H

#include <AbstractRoboPart.h>
#include <RoboBrain.h>

class AbstractRoboPart {
    public:

    const String m_part_name;

    AbstractRoboPart(RoboBrain& robo_brain, const String part_name);

    virtual void setup() = 0;
};

AbstractRoboPart::AbstractRoboPart(RoboBrain& robo_brain, const String part_name) :
    m_part_name(part_name)
{
    robo_brain.add_part(this);
}

#endif