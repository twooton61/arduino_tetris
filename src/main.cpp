/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("loop");

  delay(1000);
}