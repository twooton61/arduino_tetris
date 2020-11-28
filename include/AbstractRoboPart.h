#ifndef ABSTRACT_ROBO_PART_H
#define ABSTRACT_ROBO_PART_H

class RoboBrain;

class AbstractRoboPart {
    public:

    const String m_part_name;

    AbstractRoboPart(RoboBrain& robo_brain, const String part_name);

    inline String name() {
        return m_part_name;
    }

    virtual void setup() = 0;
};

#endif