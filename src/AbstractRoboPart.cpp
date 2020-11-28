#include <RoboBrain.h>
#include <AbstractRoboPart.h>

AbstractRoboPart::AbstractRoboPart(RoboBrain& robo_brain, const String part_name) :
    m_part_name(part_name)
{
    robo_brain.add_part(*this);
}
