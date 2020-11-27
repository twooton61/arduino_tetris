#ifndef ROBOIRRECEIVER_H
#define ROBOIRRECEIVER_H

#include <Arduino.h>
#include <IRremote.h>
#include <RoboBrain.h>

class RoboIRReceiver : AbstractRoboPart {
    const int m_pin = 0;
    IRrecv m_ir_receiver;
    decode_results ir_receiver_results;
    unsigned long m_last_ir_code = 0;

    public:
    static const unsigned long IR_CODE_LEFT = 16716015;
    static const unsigned long IR_CODE_RIGHT = 16734885;
    static const unsigned long IR_CODE_DOWN = 16730805;
    static const unsigned long IR_CODE_UP = 16718055;
    static const unsigned long IR_CODE_HOLDING = 4294967295;

    RoboIRReceiver(RoboBrain& robo_brain, const int pin) :
        m_pin(pin),
        m_ir_receiver(pin)
    {
        robo_brain.add_part(this);
    }

    inline void setup() override {
        m_ir_receiver.enableIRIn();
    }
};

#endif