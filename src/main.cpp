/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <MaxMatrix.h>
#include <RoboIRReceiver.h>

const int MAX_MATRICIES_ON_BOARD = 2;
const int MAX_ROWS = 8;
const int MAX_COLS = 16;
const int MAX_MATRIX_DIN_PIN = DIGITAL_IO_PIN(11);
const int MAX_MATRIX_CS_LOAD_PIN = DIGITAL_IO_PIN(10);
const int MAX_MATRIX_CLK_PIN = DIGITAL_IO_PIN(13);
MaxMatrix max_matrix(MAX_MATRIX_DIN_PIN, MAX_MATRIX_CS_LOAD_PIN, MAX_MATRIX_CLK_PIN, MAX_MATRICIES_ON_BOARD);
int current_matrix_x = 0;
int current_matrix_y = 0;

RoboBrain robo_brain;

RoboIRReceiver robo_ir_receiver_(robo_brain, DIGITAL_IO_PIN(7));

void setup()
{
  Serial.begin(9600);

  max_matrix.init();
  max_matrix.setIntensity(0);
}

inline void clear_current() {
  max_matrix.setDot(current_matrix_x, current_matrix_y, 0);
}

inline void move_x(const int movement)
{
  clear_current();

  int new_x = (current_matrix_x + movement);
  if(new_x < 0) {
    new_x = 0;
  }
  else if(new_x >= MAX_COLS ) {
    new_x = MAX_COLS -1;
  }

  current_matrix_x = new_x;
}

inline void move_y(const int movement)
{
  clear_current();

  int new_y = (current_matrix_y + movement);
  if(new_y < 0) {
    new_y = 0;
  }
  else if(new_y >= MAX_COLS ) {
    new_y = MAX_COLS -1;
  }

  current_matrix_y = new_y;
}

void loop()
{
  /*
  Serial.print("x: ");
  Serial.print(current_matrix_x);
  Serial.print(" y: ");
  Serial.println(current_matrix_y);

  if (ir_receive.decode(&ir_receiver_results)) {
    const unsigned long ir_code = ir_receiver_results.value;
    Serial.print("IR code: ");
    Serial.println(ir_code);

    unsigned long ir_code_to_consider = 0;

    if(ir_code == IR_CODE_HOLDING) {
      ir_code_to_consider = last_ir_code;
    }
    else {
      ir_code_to_consider = ir_code;
      last_ir_code = ir_code;
    }

    Serial.print("IR code to consider: ");
    Serial.println(ir_code_to_consider);

    switch(ir_code_to_consider) {
      case IR_CODE_LEFT:
        move_x(-1);
        break;
      case IR_CODE_RIGHT:
        move_x(1);
        break;
      case IR_CODE_UP:
        move_y(-1);
        break;
      case IR_CODE_DOWN:
        move_y(1);
        break;
      default:
        move_x(1);
        break;
    }
    ir_receive.resume();
  }
  else {
    // move_x(-1);
  }

  max_matrix.setDot(current_matrix_x, current_matrix_y, 1);
*/
  delay(500);
}