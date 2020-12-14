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
const int BOARD_COLS = LED_COLS_PER_MATRIX;
const int BOARD_ROWS = LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX;

// upside down
byte dot_pile[BOARD_ROWS] = {
  0b11000111,
  0b11000101,
  0b10000101,
  0b10000101
};

Tetris::Peice* active_peice = NULL;
void clear_peice(const Tetris::Peice& peice);
void draw_peice(const Tetris::Peice& peice);
void draw_dot_pile(byte* dote_pile);
void draw(byte* shape, const int size, const int y_offset);
bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, byte* dote_pile);
void commit_peice_to_dot_pile(Tetris::Peice& peice, byte* dote_pile);

bool game_over = false;
int period = 300;
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

    byte sad_face[] = {
      0b00000000,
      0b00100100,
      0b00100100,
      0b00000000,
      0b00111100,
      0b01000010,
      0b01000010,
      0b00000000
    };

    draw(sad_face, 8, BOARD_ROWS);

    delay(1000);
    return;
  }

  if (active_peice == NULL) {
    static const int TOTAL_POSSIBLE_PEICES = 7;
    const int peice_index = random(0, TOTAL_POSSIBLE_PEICES - 1);
    switch (peice_index){
      case 0:
        active_peice = new Tetris::SquarePeice(0, BOARD_ROWS);
        break;
      case 1:
        active_peice = new Tetris::IPeice(0, BOARD_ROWS);
        break;
      case 2:
        active_peice = new Tetris::JPeice(0, BOARD_ROWS);
        break;
      case 3:
        active_peice = new Tetris::LPeice(0, BOARD_ROWS);
        break;
      case 4:
        active_peice = new Tetris::SPeice(0, BOARD_ROWS);
        break;
      case 5:
        active_peice = new Tetris::TPeice(0, BOARD_ROWS);
        break;
      case 6:
        active_peice = new Tetris::ZPeice(0, BOARD_ROWS);
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
        peice.x(peice.x() + 1);
      }

      if (peice.x() != 0 && left_button.is_pressed()) {
        peice.x(peice.x() - 1);
      }

      if (down_button.is_pressed()) {
        peice.y(peice.y() - 1);
      }

      if (up_button.is_pressed()) {
        peice.rotate();
      }

      bool peice_commited = false;
      if (peice.y() > 0){
        if (peice_will_collide_with_dot_pile(peice, dot_pile)){

          if (peice.y() >= BOARD_ROWS - 1) {
            game_over = true;
          }

          commit_peice_to_dot_pile(peice, dot_pile);
          peice_commited = true;
        }
        else {
          peice.y(peice.y() - 1);
        }
      }
      else {
        // row hit bottom
        commit_peice_to_dot_pile(peice, dot_pile);
        peice_commited = true;
      }

      if(!peice_commited) {
        draw_peice(peice);
      }
    }

    draw_dot_pile(dot_pile);
  }
}

bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, byte* dote_pile)
{
  for (int y = peice.next_y(); y < (peice.next_y() + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      if (peice.hits_shape(y - peice.next_y(), x - peice.x())) {
        const byte row_value = dot_pile[y];

        if (row_value & (1 << (7 - x))) {
          return true;
        }
      }
    }
  }

  return false;
}

void commit_peice_to_dot_pile(Tetris::Peice& peice, byte* dote_pile)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        if (y >= BOARD_ROWS) {
          game_over = true;
          return;
        }

        dot_pile[y] |= 1 << (7 - x);
      }
    }
  }

  // clear_peice(peice);

  delete active_peice;
  active_peice = NULL;
}

void draw_dot_pile(byte* dote_pile)
{
  for (int y = 0; y < BOARD_ROWS; ++y) {
    bool row_has_dot = false;

    for (int x = 0; x < BOARD_COLS; ++x) {
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

void draw(byte* shape, const int size, const int y_offset = 0)
{
  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < BOARD_COLS; ++x) {
      const byte col = shape[size - y - 1];

      // if bit is set on column
      const bool hit = col & (1 << (7 - x));
      robo_matrix.set_led_on(x, y + y_offset, hit);
    }
  }
}

void clear_peice(const Tetris::Peice& peice)
{
  if (peice.y() < 0) {
    return;
  }

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      robo_matrix.set_led_on(x, y, false);
    }
  }
}

void draw_peice(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}
