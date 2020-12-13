#ifndef TETRIS_LPEICE_H_
#define TETRIS_LPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>


namespace Tetris
{
class LPeice : public Peice
{
public:
  LPeice(const int x, const int y) :
    Peice(x, y, l_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 3;
  byte l_peice[CONTAINER_DIMENSION * ROTATION_PHASES] = {
    0b10000000,
    0b10000000,
    0b11000000,

    0b00000000,
    0b00100000,
    0b11100000,

    0b01100000,
    0b00100000,
    0b00100000,


    0b11100000,
    0b10000000,
    0b00000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_LPEICE_H_
