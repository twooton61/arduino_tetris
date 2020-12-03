#ifndef ROBO_BUTTON_H_
#define ROBO_BUTTON_H_

#include <Arduino.h>
#include <Robo/AbstractPart.h>

namespace Robo {
class Button : AbstractPart {
    const int m_pin;

    public:

    Button(Brain& robo_brain, const int pin);

    void setup() override;
    const bool is_pressed() const;
};
}  // namespace Robo

#endif  // ROBO_BUTTON_H_
