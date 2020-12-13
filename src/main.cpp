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
#include <Tetris/IPeice.h>
#include <Tetris/JPeice.h>
#include <Tetris/LPeice.h>
#include <Tetris/SPeice.h>
#include <Tetris/SquarePeice.h>
#include <Tetris/TPeice.h>
#include <Tetris/ZPeice.h>

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
byte dot_pile[LED_ROWS] = {
  0b11000111,
  0b11000101,
  0b10000101,
  0b10000101
};

Tetris::Peice* active_peice = NULL;
void clear_peice(const Tetris::Peice& peice);
void draw_peice(const Tetris::Peice& peice);
void draw_dot_pile(byte* dote_pile);
bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, byte* dote_pile);
void commit_peice_to_dot_pile(Tetris::Peice& peice, byte* dote_pile);

bool game_over = false;
int period = 10;
unsigned long time_now = 0;

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  randomSeed(analogRead(0));

  Log::init();

  robo_brain.setup();

  robo_matrix.set_row_on(LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX, true);
}

void loop()
{
  if (game_over) {
    Serial.println("Game Over");
    delay(1000);
    return;
  }

  if (active_peice == NULL) {
    static const int TOTAL_POSSIBLE_PEICES = 7;
    switch (random(0, TOTAL_POSSIBLE_PEICES - 1)){
      case 0:
        active_peice = new Tetris::SquarePeice(0, LED_ROWS);
        break;
      case 1:
        active_peice = new Tetris::IPeice(0, LED_ROWS);
        break;
      case 2:
        active_peice = new Tetris::JPeice(0, LED_ROWS);
        break;
      case 3:
        active_peice = new Tetris::LPeice(0, LED_ROWS);
        break;
      case 4:
        active_peice = new Tetris::SPeice(0, LED_ROWS);
        break;
      case 5:
        active_peice = new Tetris::TPeice(0, LED_ROWS);
        break;
      case 6:
        active_peice = new Tetris::ZPeice(0, LED_ROWS);
        break;

    }
  }

  Tetris::Peice& peice = *active_peice;

  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  if (millis() >= time_now + period){
    time_now += period;

    if (active_peice != NULL) {
      clear_peice(peice);

      if (right_button.is_pressed()) {
        active_peice->x(active_peice->x() + 1);
      }

      if (left_button.is_pressed()) {
        active_peice->x(active_peice->x() - 1);
      }

      if (down_button.is_pressed()) {
        active_peice->y(active_peice->y() - 1);
      }

      if (up_button.is_pressed()) {
        active_peice->y(active_peice->y() + 1);
      }

      if (active_peice->y() > 0){
        if (peice_will_collide_with_dot_pile(peice, dot_pile)){

          if (active_peice->y() >= LED_ROWS - 1) {
            game_over = true;
          }

          commit_peice_to_dot_pile(peice, dot_pile);
        }
        else {
          active_peice->y(active_peice->y() - 1);
        }
      }
      else {
        // row hit bottom
        commit_peice_to_dot_pile(peice, dot_pile);
      }

      draw_peice(peice);
    }

    draw_dot_pile(dot_pile);
  }
}

bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, byte* dote_pile)
{
  for (int y = active_peice->next_y(); y < (active_peice->next_y() + active_peice->height()) && y < LED_ROWS; ++y) {
    for (int x = active_peice->x(); x < (active_peice->x() + active_peice->width()) && x < LED_COLS; ++x) {
      if (active_peice->hits_shape(y - active_peice->next_y(), x - active_peice->x())) {
        const byte col = dot_pile[y];

        // if bit is set on column
        if (col & (1 << (7 - x))) {
          // Serial.println("Collides at:");
          // Serial.print("y: ");
          // Serial.println(y);

          // Serial.print("x: ");
          // Serial.println(x);
          return true;
        }
      }
    }
  }

  return false;
}

void commit_peice_to_dot_pile(Tetris::Peice& peice, byte* dote_pile)
{
  // Serial.println("!!!!!!!!!!! STARTING COMMIT");

  for (int y = active_peice->y(); y < (active_peice->y() + active_peice->height()) && y < LED_ROWS; ++y) {
    for (int x = active_peice->x(); x < (active_peice->x() + active_peice->width()) && x < LED_COLS; ++x) {
      if (active_peice->hits_shape(y - active_peice->y(), x - active_peice->x())) {
        if (y >= LED_ROWS) {
          game_over = true;
          return;
        }
        const byte dot_pile_row = dot_pile[y];
        // Serial.println(String("Dot pile at: ") + String(y));
        // Serial.println(dot_pile_row, BIN);

        // Serial.println("Peice row:");
        // Serial.println(active_peice_row_shifted, BIN);

        // draw the shape adjusted for the x position on board
        dot_pile[y] = dot_pile_row | (0b000000001 << (7 - x));
        // Serial.println("Is now:");

        // Serial.println(dot_pile[y], BIN);
        // Serial.println("==========================");
      }
    }
  }

  delete active_peice;
  active_peice = NULL;

  // Serial.println("!!!!!!!!!!! ENDING COMMIT");
}

void draw_dot_pile(byte* dote_pile)
{
  for (int y = 0; y < LED_ROWS; ++y) {
    bool row_has_dot = false;

    for (int x = 0; x < LED_COLS; ++x) {
      const byte col = dot_pile[y];

      // if bit is set on column
      if (col & (1 << (7 - x))) {
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

void clear_peice(const Tetris::Peice& peice)
{
  if (active_peice->y() < 0) {
    return;
  }

  for (int y = active_peice->y(); y < (active_peice->y() + active_peice->height()) && y < LED_ROWS; ++y) {
    for (int x = active_peice->x(); x < (active_peice->x() + active_peice->width()) && x < LED_COLS; ++x) {
      robo_matrix.set_led_on(x, y, false);
    }
  }
}

void draw_peice(const Tetris::Peice& peice)
{
  for (int y = active_peice->y(); y < (active_peice->y() + active_peice->height()) && y < LED_ROWS; ++y) {
    for (int x = active_peice->x(); x < (active_peice->x() + active_peice->width()) && x < LED_COLS; ++x) {
      if (active_peice->hits_shape(y - active_peice->y(), x - active_peice->x())) {
        robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}
