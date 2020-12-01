#ifndef HELPERS_H_
#define HELPERS_H_

#include <Arduino.h>

#define DIGITAL_IO_PIN(pin) pin

#define ROBO_DEBUGGER true

namespace Log {
inline void init()
{
    #if ROBO_DEBUGGER == false
    Serial.begin(9600);
    #endif
}

inline void print(const String& message)
{
    #if ROBO_DEBUGGER == false
    Serial.print(message);
    #endif
}

inline void println(const String& message)
{
    #if ROBO_DEBUGGER == false
    Serial.println(message);
    #endif
}
}  // namespace Log

#endif  // HELPERS_H_
