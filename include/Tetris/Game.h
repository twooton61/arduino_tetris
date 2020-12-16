#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include <Helpers.h>
#include <Tetris/Peice.h>
#include <Robo/Matrix.h>

namespace Tetris
{
class Board
{



Robo::Matrix& robo_matrix;

public:

static const int LEDS_TO_USE_FOR_BOARD = 3;
static const int LED_COLS_PER_MATRIX = 8;
static const int LED_ROWS_PER_MATRIX = 8;
static const int BOARD_COLS = LED_COLS_PER_MATRIX;
static const int BOARD_ROWS = LEDS_TO_USE_FOR_BOARD * LED_ROWS_PER_MATRIX;


explicit Board(Robo::Matrix& robo_matrix) :
  robo_matrix(robo_matrix)
{

}

bool peice_will_collide_with_dot_pile(Tetris::Peice& peice, int y_drop)
{
  for (int y = peice.next_y(y_drop); y < (peice.next_y(y_drop) + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
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

void commit_peice_to_dot_pile(Tetris::Peice** peice_ptr)
{
  Tetris::Peice& peice = **peice_ptr;
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < BOARD_ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        if (y >= BOARD_ROWS) {
          // TODO game_over = true;
          return;
        }

        dot_pile[y] |= 1 << (7 - x);
      }
    }
  }

  // clear_peice(peice);


}

void draw_dot_pile()
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

void clear_peice_unbounded(const Tetris::Peice& peice)
{
  if (peice.y() < 0) {
    return;
  }

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (BOARD_COLS * 4); ++y) {
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

void draw_peice_unbounded(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (BOARD_COLS * 4); ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < BOARD_COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}

private:
// upside down
byte dot_pile[BOARD_ROWS] = {
  0b11000111,
  0b11000101,
  0b10000101,
  0b10000101
};

};
}  // namespace Tetris

#endif  // TETRIS_BOARD_H_
