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

const int LED_COLS = 8;
const int LED_ROWS = 32;
int dot_pile[LED_COLS][LED_ROWS] = {{ 0 }};

struct Peice {
  static const int MAX_WIDTH = 2;
  static const int MAX_HEIGHT = 2;
  int x = 1;
  int y = 1;
  int shape [MAX_WIDTH][MAX_HEIGHT] = {
    { 1, 1 },
    { 0, 1 }
  };
} peice;

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
  // Log::println("loop");

  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  robo_matrix.clear();

  for (int x = 0; x < LED_COLS; ++x) {
    for (int y = 0; y < LED_ROWS; ++y) {
      if (
        (x >= peice.x && x <= (peice.x + (Peice::MAX_WIDTH - 1))) &&
        (y >= peice.y && y <= (peice.y + (Peice::MAX_HEIGHT - 1))) &&
        peice.shape[y - peice.y][x - peice.x]
      ) {
        Log::println(String("px: ") + String(peice.x) + String("col: ") + String(x));
        robo_matrix.set_led_on(x, y, true);
      }
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

  if (up_button.is_pressed()) {
    peice.y++;
  }

  // peice.y--;

  delay(1000);
}
