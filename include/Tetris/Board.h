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

explicit Board(Robo::Matrix& robo_matrix);
bool peice_will_collide_with_dot_pile(Peice& peice, int y_drop);
void commit_peice_to_dot_pile(Peice& peice);
void clear_board();
bool clean_dot_pile();
void compact_dot_pile();
void draw_dot_pile(Tetris::Peice* const peice);
void draw(const byte* const shape, const int size, const int y_offset = 0);
void clear_peice(const Peice& peice);
void clear_peice_unbounded(const Peice& peice);
void draw_peice(const Peice& peice);
void draw_peice_unbounded(const Peice& peice);
Peice* generate_new_peice(const int x, const int y) const;

private:
// upside down
byte m_dot_pile[ROWS] = {
  0b01111111,
  0b01111111,
  0b01010101,
  0b01000101
};

Robo::Matrix& m_robo_matrix;
static const byte EMPTY_ROW = 0b00000000;
static const byte FULL_ROW = 0b11111111;
};
}  // namespace Tetris

#endif  // TETRIS_BOARD_H_
