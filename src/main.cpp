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
#include <Tetris/LPeice.h>
#include <Tetris/SquarePeice.h>

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

const int LEDS_TO_USE_FOR_BOARD = 3;
const int LED_COLS_PER_MATRIX = 8;
const int LED_ROWS_PER_MATRIX = 8;
const int LED_COLS = LED_COLS_PER_MATRIX;
const int LED_ROWS = LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX;

// upside down
bool dot_pile[LED_ROWS][LED_COLS] = {
  { 1, 1, 0, 0, 0, 1, 1, 1 },
  { 1, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 }
};

Tetris::LPeice peice(0, LED_ROWS);

void clear_peice();
void draw_dot_pile();
void draw_peice();

int period = 500;
unsigned long time_now = 0;

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  Log::init();

  robo_brain.setup();

  robo_matrix.set_row_on(LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX, true);
}

void loop()
{
  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  if (millis() >= time_now + period){
    time_now += period;

    clear_peice();

    if (right_button.is_pressed()) {
      peice.x(peice.x() + 1);
    }

    if (left_button.is_pressed()) {
      peice.x(peice.x() - 1);
    }

    if (down_button.is_pressed()) {
      peice.y(peice.y() - 1);
    }

    if (up_button.is_pressed()) {
      peice.y(peice.y() + 1);
    }

    if (peice.y() > 0) {
      peice.y(peice.y() - 1);
    }

    draw_peice();

    draw_dot_pile();
  }
}



void draw_dot_pile()
{
  for (int y = 0; y < LED_ROWS; ++y) {
    bool row_has_dot = false;
    for (int x = 0; x < LED_COLS; ++x) {
      if (
        dot_pile[y][x]
      ) {
        robo_matrix.set_led_on(x, y, true);

        row_has_dot = true;
      }
    }

    // if there are no dots on a single row of a pile, we can stop drawing up
    if (!row_has_dot) {
      break;
    }
  }
}

void clear_peice()
{
  if (peice.y() < 0) {
    return;
  }

  for (int y_to_test = peice.y(); y_to_test < (peice.y() + peice.height()) && y_to_test < LED_ROWS; ++y_to_test) {
    for (int x_to_test = peice.x(); x_to_test < (peice.x() + peice.width()) && x_to_test < LED_COLS; ++x_to_test) {

        //  && peice.hits_shape(y - peice.y(), x - peice.x())

        robo_matrix.set_led_on(x_to_test, y_to_test, false);
    }
  }
}

void draw_peice()
{
  for (int y_to_test = peice.y(); y_to_test < (peice.y() + peice.height()) && y_to_test < LED_ROWS; ++y_to_test) {
    for (int x_to_test = peice.x(); x_to_test < (peice.x() + peice.width()) && x_to_test < LED_COLS; ++x_to_test) {
      if (peice.hits_shape(y_to_test - peice.y(), x_to_test - peice.x())) {
        robo_matrix.set_led_on(x_to_test, y_to_test, true);
      }
    }
  }
}
