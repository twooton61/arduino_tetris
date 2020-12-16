#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include <Helpers.h>
#include <Tetris/Peice.h>
#include <Tetris/IPeice.h>
#include <Tetris/JPeice.h>
#include <Tetris/LPeice.h>
#include <Tetris/SPeice.h>
#include <Tetris/SquarePeice.h>
#include <Tetris/TPeice.h>
#include <Tetris/ZPeice.h>
#include <Robo/Matrix.h>

namespace Tetris
{
class Board
{

public:

static const int LEDS_TO_USE_FOR_BOARD = 3;
static const int LED_COLS_PER_MATRIX = 8;
static const int LED_ROWS_PER_MATRIX = 8;
static const int COLS = LED_COLS_PER_MATRIX;
static const int ROWS = LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX;


explicit Board(Robo::Matrix& robo_matrix) :
  robo_matrix(robo_matrix)
{

}

bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, int y_drop)
{
  for (int y = peice.next_y(y_drop); y < (peice.next_y(y_drop) + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.next_y(y_drop), x - peice.x())) {
        const byte row_value = dot_pile[y];

        if (row_value & (1 << (7 - x))) {
          return true;
        }
      }
    }
  }

  return false;
}

void commit_peice_to_dot_pile(Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        if (y >= ROWS) {
          return;
        }

        dot_pile[y] |= 1 << (7 - x);
      }
    }
  }
}

void draw_dot_pile()
{
  for (int y = 0; y < ROWS; ++y) {
    bool row_has_dot = false;

    for (int x = 0; x < COLS; ++x) {
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
    for (int x = 0; x < COLS; ++x) {
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

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      robo_matrix.set_led_on(x, y, false);
    }
  }
}

void clear_peice_unbounded(const Tetris::Peice& peice)
{
  if (peice.y() < 0) {
    return;
  }

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (COLS * 4); ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      robo_matrix.set_led_on(x, y, false);
    }
  }
}

void draw_peice(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}

void draw_peice_unbounded(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (COLS * 4); ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}

Tetris::Peice* generate_new_peice() const
{
  static const int TOTAL_POSSIBLE_PEICES = 7;
  const int peice_index = random(0, TOTAL_POSSIBLE_PEICES - 1);

  Tetris::Peice* peice =  NULL;
  switch (peice_index){
    case 0:
      peice = new Tetris::SquarePeice(0, 0);
      break;
    case 1:
      peice = new Tetris::IPeice(0, 0);
      break;
    case 2:
      peice = new Tetris::JPeice(0, 0);
      break;
    case 3:
      peice = new Tetris::LPeice(0, 0);
      break;
    case 4:
      peice = new Tetris::SPeice(0, 0);
      break;
    case 5:
      peice = new Tetris::TPeice(0, 0);
      break;
    case 6:
      peice = new Tetris::ZPeice(0, 0);
      break;
  }

  return peice;
}

private:
// upside down
byte dot_pile[ROWS] = {
  0b11000111,
  0b11000101,
  0b10000101,
  0b10000101
};

Robo::Matrix& robo_matrix;
};
}  // namespace Tetris

#endif  // TETRIS_BOARD_H_
