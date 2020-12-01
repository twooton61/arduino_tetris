#include <Arduino.h>
#include <Robo/IRReceiver.h>
#include <Helpers.h>

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

    const bool is_holding_button = ir_code == 4294967295;
    if (is_holding_button) {
        ir_code_to_consider = m_last_ir_code;
    }
    else {
        ir_code_to_consider = ir_code;
        m_last_ir_code = ir_code;
    }

    Log::print("IR code: ");
    Log::print(String(ir_code));
    Log::print(" IR to consider: ");
    Log::println(String(ir_code_to_consider));

    return ir_code_to_consider;
}

boolean IRReceiver::left_pressed() {
    switch (get_ir_code()) {
        case 2351064443UL:
        case 16716015UL:
            Log::println("left pressed");

            return true;
            break;
    }

    return false;
}

boolean IRReceiver::right_pressed() {
    switch (get_ir_code()) {
        case 16734885UL:
            Log::println("right pressed");

            return true;
            break;
    }

    return false;
}

boolean IRReceiver::up_pressed() {
    switch (get_ir_code()) {
        case 16718055UL:
            Log::println("up pressed");

            return true;
            break;
    }

    return false;
}

boolean IRReceiver::down_pressed() {
    switch (get_ir_code()) {
        case 16730805UL:
            Log::println("down pressed");

            return true;
            break;
    }

    return false;
}

void IRReceiver::resume() {
    m_ir_receiver.resume();
}
}  // namespace Robo
