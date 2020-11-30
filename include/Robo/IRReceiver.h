#ifndef ROBO_IRRECEIVER_H_
#define ROBO_IRRECEIVER_H_

#include <Arduino.h>
#include <Robo/AbstractPart.h>
#include <IRremote.h>

namespace Robo {
class IRReceiver : Robo::AbstractPart {
 public:
    static const unsigned long IR_CODE_HOLDING = 4294967295;

    IRReceiver(Robo::Brain& robo_brain, const int pin);

    void setup() override;

    bool detect_signal();

    unsigned long get_ir_code();

    boolean left_pressed();
    boolean right_pressed();
    boolean up_pressed();
    boolean down_pressed();

    void resume();

 private:
    const int m_pin = 0;
    IRrecv m_ir_receiver;
    decode_results m_ir_receiver_results;
    unsigned long m_last_ir_code = 0;
};
}  // namespace Robo

#endif  // ROBO_IRRECEIVER_H_
