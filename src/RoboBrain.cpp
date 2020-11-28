#include <RoboBrain.h>
#include <Arduino.h>

#include <AbstractRoboPart.h>

class AbstractRoboPartNode {
    AbstractRoboPart& m_robo_part;
    AbstractRoboPartNode* m_next_node;

    public:
    explicit AbstractRoboPartNode(AbstractRoboPart& robo_part) :
        m_robo_part(robo_part),
        m_next_node(NULL)
    {
    }

    inline void set_next_node(AbstractRoboPartNode* next_node) {
        m_next_node = next_node;
    }

    inline AbstractRoboPartNode* get_next_node() {
        return m_next_node;
    }

    inline AbstractRoboPart& get_robo_part() {
        return m_robo_part;
    }
};

RoboBrain::RoboBrain() :
    m_last_part_added_node(NULL)
{
}

void RoboBrain::add_part(AbstractRoboPart& robo_part) {
    AbstractRoboPartNode* new_part_node = new AbstractRoboPartNode(robo_part);

    if(m_first_part_added_node == NULL) {
        m_first_part_added_node = new_part_node;
        m_last_part_added_node = new_part_node;
    }
    else {
        m_last_part_added_node->set_next_node(new_part_node);
        m_last_part_added_node = new_part_node;
    }
}

void RoboBrain::setup() {
    AbstractRoboPartNode* current_node = m_first_part_added_node;
    while(current_node != NULL) {
        AbstractRoboPart& robo_part = current_node->get_robo_part();
        Serial.println(String("setting up robo part: ") + robo_part.name());
        robo_part.setup();
        current_node = current_node->get_next_node();
    }
}
