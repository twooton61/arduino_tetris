/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <IRremote.h>
#include <MaxMatrix.h>

IRrecv ir_receive(DIGITAL_IO_PIN(7));
decode_results ir_receiver_results;

const int MAX_MATRICIES_ON_BOARD = 1;
const int MAX_ROWS = 8;
const int MAX_COLS = 8;
const int MAX_MATRIX_DIN_PIN = DIGITAL_IO_PIN(11);
const int MAX_MATRIX_CS_LOAD_PIN = DIGITAL_IO_PIN(10);
const int MAX_MATRIX_CLK_PIN = DIGITAL_IO_PIN(13);
MaxMatrix max_matrix(MAX_MATRIX_DIN_PIN, MAX_MATRIX_CS_LOAD_PIN, MAX_MATRIX_CLK_PIN, MAX_MATRICIES_ON_BOARD);

void setup()
{
  Serial.begin(9600);

  ir_receive.enableIRIn();

  max_matrix.init();
  max_matrix.setIntensity(0);
}

void loop()
{
  Serial.println("Loop");

  max_matrix.setDot(1, 1, 1);

  if (ir_receive.decode(&ir_receiver_results)) {
    Serial.println(ir_receiver_results.value, HEX);
    ir_receive.resume();
  }

  delay(600);
}