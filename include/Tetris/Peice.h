#ifndef TETRIS_PEICE_H_
#define TETRIS_PEICE_H_

#include <Robo/Matrix.h>
#include <Helpers.h>
namespace Tetris
{
class Peice
{
public:
  Peice(const int x, const int y) :
    m_x(x),
    m_y(y)
  {
  }

  const int x() { return m_x; }
  void x(const int x) { m_x = x; }
  const int y() { return m_y; }
  void y(const int y) { m_y = y; }
  const int height() { return m_height; }
  const int width() { return m_width; }
  const bool hits_shape(const int y, const int x) { return shape[y][x]; }

private:
  int m_height = 2;
  int m_width = 2;
  int m_x;
  int m_y;

  bool shape [2][2] = {
    // upside down
    { 1, 1 },
    { 0, 1 }
  };
};


}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
