#include <Arduino.h>
#include <Robo/IRReceiver.h>

namespace Robo {
IRReceiver::IRReceiver(Brain& robo_brain, const int pin) :
    AbstractPart(robo_brain, "IR Receiver"),
    m_pin(pin),
    m_ir_receiver(pin)
{
}

void IRReceiver::setup() {
    m_ir_receiver.enableIRIn();
}

bool IRReceiver::detect_signal() {
    return m_ir_receiver.decode(&m_ir_receiver_results);
}

IRReceiver::IRCode IRReceiver::get_ir_code() {
    IRCode ir_code = m_ir_receiver_results.value;
    IRCode ir_code_to_consider = 0;

    if (is_holding()) {
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

boolean IRReceiver::is_holding() {
    return get_ir_code() == 4294967295;
}


boolean IRReceiver::left_pressed() {
    switch (get_ir_code()) {
        case 2351064443UL:
        case 16716015UL:
            Serial.println("left pressed");
            return true;
            break;
    }

    return false;
}

boolean IRReceiver::right_pressed() {
    switch (get_ir_code()) {
        case 16734885UL:
            Serial.println("right pressed");
            return true;
            break;
    }

    return false;
}

boolean IRReceiver::up_pressed() {
    switch (get_ir_code()) {
        case 16718055UL:
            Serial.println("up pressed");
            return true;
            break;
    }

    return false;
}

boolean IRReceiver::down_pressed() {
    switch (get_ir_code()) {
        case 16730805UL:
            Serial.println("down pressed");
            return true;
            break;
    }

    return false;
}

void IRReceiver::resume() {
    m_ir_receiver.resume();
}
}  // namespace Robo
