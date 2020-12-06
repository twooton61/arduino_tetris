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
#include <Robo/Button.h>

#ifdef ROBO_DEBUGGER
#include <avr8-stub.h>
#endif

Robo::Brain robo_brain;

Robo::Matrix robo_matrix(
  robo_brain,
  MATRIX_DIN_PIN(11),
  MATRIX_CS_PIN(10),
  MATRIX_CLK_PIN(12),
  MATRICIES_ON_BOARD(4)
);

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(7));

Robo::Button up_button(robo_brain, DIGITAL_IO_PIN(2));
Robo::Button down_button(robo_brain, DIGITAL_IO_PIN(3));
Robo::Button left_button(robo_brain, DIGITAL_IO_PIN(4));
Robo::Button right_button(robo_brain, DIGITAL_IO_PIN(5));

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  Log::init();

  robo_brain.setup();

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

  if (up_button.is_pressed()) {
    Log::println("up button pressed");

    robo_matrix.move_y(1);
  }
  if (down_button.is_pressed()) {
    Log::println("down button pressed");
    robo_matrix.move_y(-1);
  }
  if (left_button.is_pressed()) {
    Log::println("left button pressed");
    robo_matrix.move_x(-1);
  }
  if (right_button.is_pressed()) {
    Log::println("right button pressed");
    robo_matrix.move_x(1);
  }

  delay(500);
}
