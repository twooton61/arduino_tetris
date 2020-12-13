#ifndef TETRIS_ZPEICE_H_
#define TETRIS_ZPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>


namespace Tetris
{
class ZPeice : public Peice
{
public:
  ZPeice(const int x, const int y) :
    Peice(x, y, z_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 3;
  byte z_peice[CONTAINER_DIMENSION * ROTATION_PHASES] = {
    0b11000000,
    0b01100000,
    0b00000000,

    0b01000000,
    0b11000000,
    0b10000000,

    0b11000000,
    0b01000000,
    0b01100000,

    0b00000000,
    0b01100000,
    0b11000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_ZPEICE_H_
