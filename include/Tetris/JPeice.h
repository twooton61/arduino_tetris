#ifndef TETRIS_JPEICE_H_
#define TETRIS_JPEICE_H_

#include <Tetris/Peice.h>
#include <Helpers.h>


namespace Tetris
{
class JPeice : public Peice
{
public:
  JPeice(const int x, const int y) :
    Peice(x, y, l_peice, CONTAINER_DIMENSION)
  {
  }
private:
  static const int CONTAINER_DIMENSION = 3;
  byte l_peice[CONTAINER_DIMENSION] = {
    0b01000000,
    0b01000000,
    0b11000000
  };
};
}  // namespace Tetris

#endif  // TETRIS_JPEICE_H_
