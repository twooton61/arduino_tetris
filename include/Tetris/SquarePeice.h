#ifndef TETRIS_SQUAREPEICE_H_
#define TETRIS_SQUAREPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>

namespace Tetris
{
class SquarePeice : public Peice
{
  static const int CONTAINER_DIMENSION = 2;
  byte square_peice[CONTAINER_DIMENSION] = {
    0b11000000,
    0b11000000
  };

public:
  SquarePeice(const int x, const int y) :
    Peice(x, y, square_peice, CONTAINER_DIMENSION)
  {
  }
};
}  // namespace Tetris

#endif  // TETRIS_SQUAREPEICE_H_
