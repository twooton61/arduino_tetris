#include <Arduino.h>
#include <RoboIRReceiver.h>

RoboIRReceiver::RoboIRReceiver(RoboBrain& robo_brain, const int pin) :
    AbstractRoboPart(robo_brain, "IR Receiver"),
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

    if (ir_code == RoboIRReceiver::IR_CODE_HOLDING) {
        ir_code_to_consider = m_last_ir_code;
    }
    else {
        ir_code_to_consider = ir_code;
        m_last_ir_code = ir_code;
    }

    Serial.print("IR code: ");
    Serial.print(ir_code);
    Serial.print(" IR to consider: ");
    Serial.println(ir_code_to_consider);

    return ir_code_to_consider;
}

boolean RoboIRReceiver::left_pressed() {
    switch (get_ir_code()) {
        case 2351064443UL:
        case 16716015UL:
            Serial.println("left pressed");
            return true;
            break;
    }

    return false;
}

boolean RoboIRReceiver::right_pressed() {
    switch (get_ir_code()) {
        case 16734885UL:
            Serial.println("right pressed");
            return true;
            break;
    }

    return false;
}

boolean RoboIRReceiver::up_pressed() {
    switch (get_ir_code()) {
        case 16718055UL:
            Serial.println("up pressed");
            return true;
            break;
    }

    return false;
}

boolean RoboIRReceiver::down_pressed() {
    switch (get_ir_code()) {
        case 16730805UL:
            Serial.println("down pressed");
            return true;
            break;
    }

    return false;
}

void RoboIRReceiver::resume() {
    m_ir_receiver.resume();
}
