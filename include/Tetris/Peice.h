#ifndef TETRIS_PEICE_H_
#define TETRIS_PEICE_H_

#include <Robo/Matrix.h>

namespace Tetris
{
class Peice
{
public:
  Peice(const int x, const int y) :
    x(x),
    y(y)
  {

  }
  static const int MAX_WIDTH = 2;
  static const int MAX_HEIGHT = 2;
  int x = 0;
  int y = 0;
  bool shape [MAX_WIDTH][MAX_HEIGHT] = {
    // upside down
    { 1, 1 },
    { 0, 1 }
  };

  void draw(Robo::Matrix& robo_matrix) const
  {

  }
};
}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
