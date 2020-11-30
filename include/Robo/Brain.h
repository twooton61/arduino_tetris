#ifndef ROBO_BRAIN_H_
#define ROBO_BRAIN_H_

#include <Arduino.h>

namespace Robo {
class AbstractPartNode;
class AbstractPart;

class Brain {
    public:

    Brain();

    void add_part(AbstractPart& robo_part);

    void setup();

    private:

    AbstractPartNode* m_first_part_added_node = NULL;
    AbstractPartNode* m_last_part_added_node = NULL;
};
}  // namespace Robo

#endif  // ROBO_BRAIN_H_
