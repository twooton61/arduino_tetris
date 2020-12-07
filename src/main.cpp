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

const int COLS = 8;
const int ROWS = 32;
int dot_pile[COLS][ROWS] = {{ 0 }};

struct Peice {
  static const int MAX_WIDTH = 4;
  static const int MAX_HEIGHT = 4;
  int x = 1;
  int y = ROWS;
  int shape [MAX_WIDTH][MAX_HEIGHT] = {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 0 },
    { 1, 0, 0, 1 }
  };
} peice;


// void setup_new_peice(Peice& peice)
// {
//   peice.x = 1;
//   peice.y = ROWS;
//   for (int i = 0; i < Peice::MAX_WIDTH; i++) {
//     for (int j = 0; j < Peice::MAX_HEIGHT; j++) {
//       peice.shape[i][j] = 0;
//     }
//   }
//   peice.shape[0][0] = 1;
//   peice.shape[0][1] = 1;
//   peice.shape[0][2] = 1;
//   peice.shape[0][4] = 1;
// }

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  Log::init();

  robo_brain.setup();
}

void loop()
{
  Log::println("loop");

  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  robo_matrix.clear();

  for (int x = 1; x <= COLS; ++x) {
    for (int y = 1; y <= ROWS; ++y) {
      if (((x >= peice.x) && (x < (peice.x + 4))) &&
        ((y >= peice.y) && (y < (peice.y + 4)))
      ) {
        if (peice.shape[y - peice.y][x - peice.x]) {
          robo_matrix.set_led_on(x, y, true);
        }
      }
      // Log::println(String("x: ") + String(x));
      // Log::println(String("y: ") + String(y));
      // Log::println(String("val: ") + String(dot_pile[(x - 1)][(y -1)]));

      // const boolean is_on = dot_pile[x - 1][y -1] == 1;
      // if (is_on) {
      //   robo_matrix.set_led_on(x, y, true);
      // }
    }
  }

  if (right_button.is_pressed()) {
    peice.x++;
  }

  if (left_button.is_pressed()) {
    peice.x--;
  }

  if (down_button.is_pressed()) {
    peice.y--;
  }

  peice.y--;

  delay(500);
}
