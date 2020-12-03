/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Arduino Tetris
*/


#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/Matrix.h>
#include <Robo/IRReceiver.h>

#ifdef ROBO_DEBUGGER
#include <avr8-stub.h>
#endif

Robo::Brain robo_brain;

const int max_matricies_on_board = 2;

Robo::Matrix robo_matrix(
  robo_brain,
  DIGITAL_IO_PIN(11),
  DIGITAL_IO_PIN(10),
  DIGITAL_IO_PIN(13),
  max_matricies_on_board
);

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(7));

const int UP_BUTTON_PIN = DIGITAL_IO_PIN(2);
const int DOWN_BUTTON_PIN = DIGITAL_IO_PIN(3);
const int LEFT_BUTTON_PIN = DIGITAL_IO_PIN(4);
const int RIGHT_BUTTON_PIN = DIGITAL_IO_PIN(5);
const int PRESSED = LOW;

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  Log::init();

  robo_brain.setup();

  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

  robo_matrix.render();
}

void loop()
{
  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    const Robo::IRReceiver::IRCode ir_code = robo_ir_receiver.get_ir_code();
    if (robo_ir_receiver.is_left_code(ir_code)) {
      robo_matrix.move_x(-1);
    }
    else if (robo_ir_receiver.is_right_code(ir_code)) {
      robo_matrix.move_x(1);
    }
    else if (robo_ir_receiver.is_down_code(ir_code)) {
      robo_matrix.move_y(1);
    }
    else if (robo_ir_receiver.is_up_code(ir_code)) {
      robo_matrix.move_y(-1);
    }

    robo_ir_receiver.resume();
  }

  if (digitalRead(UP_BUTTON_PIN) == PRESSED) {
    Log::println("up button pressed");

    robo_matrix.move_y(-1);
  }
  if (digitalRead(DOWN_BUTTON_PIN) == PRESSED) {
    Log::println("down button pressed");
    robo_matrix.move_y(1);
  }
  if (digitalRead(LEFT_BUTTON_PIN) == PRESSED) {
    Log::println("left button pressed");
    robo_matrix.move_x(-1);
  }
  if (digitalRead(RIGHT_BUTTON_PIN) == PRESSED) {
    Log::println("right button pressed");
    robo_matrix.move_x(1);
  }

  delay(500);
}
