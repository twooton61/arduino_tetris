#ifndef ROBO_BRAIN_H_
#define ROBO_BRAIN_H_

#include <Arduino.h>

namespace Robo {
class AbstractPartNode;
class AbstractPart;

class Brain {
    Robo::AbstractPartNode* m_first_part_added_node = NULL;
    Robo::AbstractPartNode* m_last_part_added_node = NULL;

    public:

    Brain();

    void add_part(AbstractPart& robo_part);

    void setup();
};
}  // namespace Robo

#endif  // ROBO_BRAIN_H_
