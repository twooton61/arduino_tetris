#ifndef TETRIS_SQUAREPEICE_H_
#define TETRIS_SQUAREPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>

namespace Tetris
{
class SquarePeice : public Peice
{
  static const int CONTAINER_DIMENSION = 2;
  const char* peice[CONTAINER_DIMENSION] {
    "xx",
    "xx"
  };

public:
  SquarePeice(const int x, const int y) :
    Peice(x, y, CONTAINER_DIMENSION, peice)
  {
  }
};
}  // namespace Tetris

#endif  // TETRIS_SQUAREPEICE_H_
