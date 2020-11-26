/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <MaxMatrix.h>

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
  max_matrix.init();
  max_matrix.setIntensity(0);
}

void loop()
{
  Serial.println("loop");

  max_matrix.setDot(1,1, 1);

  delay(100);
}