#ifndef TETRIS_SPEICE_H_
#define TETRIS_SPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>


namespace Tetris
{
class SPeice : public Peice
{
public:
  SPeice(const int x, const int y) :
    Peice(x, y, s_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 3;
  byte s_peice[CONTAINER_DIMENSION] = {
    0b01100000,
    0b11000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_SPEICE_H_
