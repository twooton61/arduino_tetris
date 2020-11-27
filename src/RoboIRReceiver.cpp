#ifndef ROBO_IR_RECEIVER_H
#define ROBO_IR_RECEIVER_H

#include <Arduino.h>
#include <RoboIRReceiver.h>

RoboIRReceiver::RoboIRReceiver(RoboBrain& robo_brain, const int pin) :
    AbstractRoboPart(robo_brain),
    m_pin(pin),
    m_ir_receiver(pin)
{
}

void RoboIRReceiver::setup() {
    m_ir_receiver.enableIRIn();
}

bool RoboIRReceiver::detect_signal() {
    return m_ir_receiver.decode(&m_ir_receiver_results);
}

RoboIRReceiver::IRCode RoboIRReceiver::get_ir_code() {
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

void RoboIRReceiver::resume() {
    m_ir_receiver.resume();
}

#endif