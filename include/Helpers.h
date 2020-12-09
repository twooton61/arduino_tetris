#ifndef HELPERS_H_
#define HELPERS_H_

#include <Arduino.h>

#define DIGITAL_IO_PIN(pin) pin

#define DISABLE_COPY_AND_ASSIGN(Class) Class(const Class& x) = delete; Class& operator=(const Class x) = delete;

#define ROBO_DEBUGGER false

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
