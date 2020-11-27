#ifndef ROBOIRRECEIVER_H
#define ROBOIRRECEIVER_H

#include <Arduino.h>
#include <IRremote.h>
#include <RoboBrain.h>

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

    RoboIRReceiver(RoboBrain& robo_brain, const int pin) :
        m_pin(pin),
        m_ir_receiver(pin)
    {
        robo_brain.add_part(this);
    }

    inline void setup() override {
        m_ir_receiver.enableIRIn();
    }

    inline bool detect_signal() {
        return m_ir_receiver.decode(&m_ir_receiver_results);
    }

    inline IRCode get_ir_code() {
        IRCode ir_code = m_ir_receiver_results.value;
        IRCode ir_code_to_consider = 0;

        if(ir_code == RoboIRReceiver::IR_CODE_HOLDING) {
            ir_code_to_consider = m_last_ir_code;
        }
        else {
            ir_code_to_consider = ir_code;
            m_last_ir_code = ir_code;
        }

        return ir_code_to_consider;
    }

    inline void resume() {
        m_ir_receiver.resume();
    }
};

#endif