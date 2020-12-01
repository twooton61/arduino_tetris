#ifndef HELPERS_H_
#define HELPERS_H_

#include <Arduino.h>

#define DIGITAL_IO_PIN(pin) pin

namespace Log {
inline void init()
{
    #ifndef DEBUG
    Serial.begin(9600);
    #endif
}

inline void print(const String& message)
{
    #ifndef DEBUG
    Serial.println(message);
    #endif
}

inline void println(const String& message)
{
    #ifndef DEBUG
    Serial.println(message);
    #endif
}
}  // namespace Log

#endif  // HELPERS_H_
