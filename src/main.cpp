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


#ifdef DEBUG
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

void setup()
{
  #ifdef DEBUG
  debug_init();
  #endif

  Log::init();

  robo_brain.setup();

  robo_matrix.render();
}

void loop()
{
  Log::println("loop");
  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    if (robo_ir_receiver.left_pressed()) {
      robo_matrix.move_x(-1);
    }
    else if (robo_ir_receiver.right_pressed()) {
      robo_matrix.move_x(1);
    }
    else if (robo_ir_receiver.down_pressed()) {
      robo_matrix.move_y(1);
    }
    else if (robo_ir_receiver.up_pressed()) {
      robo_matrix.move_y(-1);
    }

    robo_ir_receiver.resume();
  }

  delay(500);
}
