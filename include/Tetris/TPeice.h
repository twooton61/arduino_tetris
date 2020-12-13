#ifndef TETRIS_TPEICE_H_
#define TETRIS_TPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>

namespace Tetris
{
class TPeice : public Peice
{
public:
  TPeice(const int x, const int y) :
    Peice(x, y, t_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 3;
  byte t_peice[CONTAINER_DIMENSION] = {
    0b11100000,
    0b01000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_TPEICE_H_
