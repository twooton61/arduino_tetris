#include <Tetris/Board.h>

namespace Tetris
{
Board::Board(Robo::Matrix& robo_matrix) :
  m_robo_matrix(robo_matrix)
{
}

bool Board::peice_will_collide_with_dot_pile(Tetris::Peice& peice, int y_drop)
{
  for (int y = peice.next_y(y_drop); y < (peice.next_y(y_drop) + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.next_y(y_drop), x - peice.x())) {
        const byte row_value = m_dot_pile[y];

        if (row_value & (1 << (7 - x))) {
          return true;
        }
      }
    }
  }

  return false;
}

void Board::commit_peice_to_dot_pile(Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        if (y >= ROWS) {
          return;
        }

        m_dot_pile[y] |= 1 << (7 - x);
      }
    }
  }
}

void Board::clear_board()
{
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      m_robo_matrix.set_led_on(x, y, false);
    }
  }
}

bool Board::clean_dot_pile()
{
  bool cleaned = false;
  Serial.println("cleaning");

  for (int y = 0; y < ROWS; ++y) {
    const byte row = m_dot_pile[y];
    if (row == FULL_ROW) {
      m_dot_pile[y] = EMPTY_ROW;
      cleaned = true;
    }
    else if (row == EMPTY_ROW) {
      break;
    }
  }

  return cleaned;
}

void Board::compact_dot_pile()
{
  // start at y = 0
  for (int y = 0; y < ROWS; ++y) {
    const byte row = m_dot_pile[y];
    // if you find a row that is blank...

    // Serial.print("looking at row :");
    // Serial.println(y);

    if (row == EMPTY_ROW) {
      // Serial.print("Row is empty:");
      // Serial.println(y);

      /// continue up until you find a solid row ..
      int row_gap = 1;
      while (m_dot_pile[y + row_gap] == EMPTY_ROW && y < ROWS) {
        row_gap++;
      }

      // Serial.print("Row gap is :");
      // Serial.println(row_gap);

      for (int z = y; z < ROWS; ++z) {
        const byte row_to_pull = (z + row_gap) >= (ROWS - 1) ? EMPTY_ROW : m_dot_pile[z + row_gap];
        // Serial.print("Pulling row :");
        // Serial.print(z + row_gap);
        // Serial.print(" to ");
        // Serial.print(z);


        // Serial.print(" value: ");
        // Serial.println(row_to_pull, BIN);
        m_dot_pile[z] = row_to_pull;
      }

      // Serial.println("Resetting y");
      // y = 0;
      // Serial.println("Done pulling rows");

    }

    // Serial.println("Looking at next row");
  }

  Serial.println("Done compacting");
}

void Board::draw_dot_pile()
{
  for (int y = 0; y < ROWS; ++y) {
    const byte row = m_dot_pile[y];
    for (int x = 0; x < COLS; ++x) {
      // if bit is set on column
      const bool is_set = (row & (1 << (7 - x)));
      m_robo_matrix.set_led_on(x, y, is_set);
    }
  }
}

void Board::draw(const byte* const shape, const int size, const int y_offset)
{
  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < COLS; ++x) {
      const byte col = shape[size - y - 1];

      // if bit is set on column
      const bool hit = col & (1 << (7 - x));
      m_robo_matrix.set_led_on(x, y + y_offset, hit);
    }
  }
}

void Board::clear_peice(const Tetris::Peice& peice)
{
  if (peice.y() < 0) {
    return;
  }

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      m_robo_matrix.set_led_on(x, y, false);
    }
  }
}

void Board::clear_peice_unbounded(const Tetris::Peice& peice)
{
  if (peice.y() < 0) {
    return;
  }

  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (COLS * 4); ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      m_robo_matrix.set_led_on(x, y, false);
    }
  }
}

void Board::draw_peice(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < ROWS; ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        m_robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}

void Board::draw_peice_unbounded(const Tetris::Peice& peice)
{
  for (int y = peice.y(); y < (peice.y() + peice.height()) && y < (COLS * 4); ++y) {
    for (int x = peice.x(); x < (peice.x() + peice.width()) && x < COLS; ++x) {
      if (peice.hits_shape(y - peice.y(), x - peice.x())) {
        m_robo_matrix.set_led_on(x, y, true);
      }
    }
  }
}

Tetris::Peice* Board::generate_new_peice(const int x, const int y) const
{
  static const int TOTAL_POSSIBLE_PEICES = 7;
  const int peice_index = random(0, TOTAL_POSSIBLE_PEICES - 1);

  Tetris::Peice* new_peice =  NULL;
  switch (peice_index){
    case 0:
      new_peice = new Tetris::SquarePeice(x, y);
      break;
    case 1:
      new_peice = new Tetris::IPeice(x, y);
      break;
    case 2:
      new_peice = new Tetris::JPeice(x, y);
      break;
    case 3:
      new_peice = new Tetris::LPeice(x, y);
      break;
    case 4:
      new_peice = new Tetris::SPeice(x, y);
      break;
    case 5:
      new_peice = new Tetris::TPeice(x, y);
      break;
    case 6:
      new_peice = new Tetris::ZPeice(x, y);
      break;
  }

  return new_peice;
}
}  // namespace Tetris
