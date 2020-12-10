#ifndef TETRIS_LPEICE_H_
#define TETRIS_LPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>

namespace Tetris
{
class LPeice : public Peice
{
  static const int CONTAINER_DIMENSION = 3;
  const char* peice[CONTAINER_DIMENSION] {
    "xx ",
    "x  ",
    "x  "
  };

public:
  LPeice(const int x, const int y) :
    Peice(x, y, CONTAINER_DIMENSION, peice)
  {
  }
};
}  // namespace Tetris

#endif  // TETRIS_LPEICE_H_
