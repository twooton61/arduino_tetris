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
const unsigned long IR_CODE_LEFT = 16716015;
const unsigned long IR_CODE_RIGHT = 16734885;
const unsigned long IR_CODE_DOWN = 16730805;
const unsigned long IR_CODE_UP = 16718055;


const int MAX_MATRICIES_ON_BOARD = 1;
const int MAX_ROWS = 8;
const int MAX_COLS = 8;
const int MAX_MATRIX_DIN_PIN = DIGITAL_IO_PIN(11);
const int MAX_MATRIX_CS_LOAD_PIN = DIGITAL_IO_PIN(10);
const int MAX_MATRIX_CLK_PIN = DIGITAL_IO_PIN(13);
MaxMatrix max_matrix(MAX_MATRIX_DIN_PIN, MAX_MATRIX_CS_LOAD_PIN, MAX_MATRIX_CLK_PIN, MAX_MATRICIES_ON_BOARD);
int matrix_x = 0;
int matrix_y = 0;

void setup()
{
  Serial.begin(9600);

  ir_receive.enableIRIn();

  max_matrix.init();
  max_matrix.setIntensity(0);
}

void loop()
{
  Serial.print("x: ");
  Serial.print(matrix_x);
  Serial.print(" y: ");
  Serial.println(matrix_y);


  max_matrix.setDot(matrix_x, matrix_y, 1);

  if (ir_receive.decode(&ir_receiver_results)) {
    Serial.println(ir_receiver_results.value);

    switch(ir_receiver_results.value) {
      case IR_CODE_LEFT:
        max_matrix.setDot(matrix_x, matrix_y, 0);
        matrix_x = (matrix_x - 1) % MAX_COLS;
        break;
      case IR_CODE_RIGHT:
        max_matrix.setDot(matrix_x, matrix_y, 0);
        matrix_x = (matrix_x + 1) % MAX_COLS;
        break;
      case IR_CODE_UP:
        max_matrix.setDot(matrix_x, matrix_y, 0);
        matrix_y = (matrix_y + 1) % MAX_ROWS;
        break;
      case IR_CODE_DOWN:
        max_matrix.setDot(matrix_x, matrix_y, 0);
        matrix_y = (matrix_y + 1) % MAX_ROWS;
        break;
    }
    ir_receive.resume();
  }

  delay(100);
}