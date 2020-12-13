#ifndef TETRIS_IPEICE_H_
#define TETRIS_IPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>

namespace Tetris
{
class IPeice : public Peice
{
public:
  IPeice(const int x, const int y) :
    Peice(x, y, peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 4;
  byte peice[CONTAINER_DIMENSION * ROTATION_PHASES] = {
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,

    0b00000000,
    0b00000000,
    0b11110000,
    0b00000000,

    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,

    0b00000000,
    0b11110000,
    0b00000000,
    0b00000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_IPEICE_H_
