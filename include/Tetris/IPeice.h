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
    Peice(x, y, i_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 4;
  byte i_peice[CONTAINER_DIMENSION] = {
    0b1000000,
    0b1000000,
    0b1000000,
    0b1000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_IPEICE_H_
