#ifndef ROBO_BRAIN_H
#define ROBO_BRAIN_H

#include <Arduino.h>

class AbstractRoboPartNode;
class AbstractRoboPart;

class RoboBrain {
    AbstractRoboPartNode* m_first_part_added_node = NULL;
    AbstractRoboPartNode* m_last_part_added_node = NULL;

    public:

    RoboBrain();

    void add_part(AbstractRoboPart& robo_part);

    void setup();
};

#endif