#ifndef ROBOIRRECEIVER_H
#define ROBOIRRECEIVER_H

#include <Arduino.h>
#include <AbstractRoboPart.h>
#include <IRremote.h>

class RoboIRReceiver : AbstractRoboPart {
    public:
    typedef unsigned long IRCode;

    private:
    const int m_pin = 0;
    IRrecv m_ir_receiver;
    decode_results m_ir_receiver_results;
    IRCode m_last_ir_code = 0;

    public:

    static const IRCode IR_CODE_LEFT = 16716015;
    static const IRCode IR_CODE_RIGHT = 16734885;
    static const IRCode IR_CODE_DOWN = 16730805;
    static const IRCode IR_CODE_UP = 16718055;
    static const IRCode IR_CODE_HOLDING = 4294967295;

    RoboIRReceiver(RoboBrain& robo_brain, const int pin);

    void setup() override;

    bool detect_signal();

    IRCode get_ir_code();

    void resume();
};

#endif