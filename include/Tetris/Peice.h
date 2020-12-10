#ifndef TETRIS_PEICE_H_
#define TETRIS_PEICE_H_

#include <Robo/Matrix.h>
#include <Helpers.h>
namespace Tetris
{
class Peice
{
public:
  Peice(const int x, const int y, const int container_dimension, const char** shape) :
    m_x(x),
    m_y(y),
    m_container_dimension(container_dimension),
    m_shape(shape)
  {
  }

  ~Peice()
  {
  }

  GET_SET(int, x)
  GET_SET(int, y)

  int height() const
  {
    return m_container_dimension;
  }

  int width() const
  {
    return m_container_dimension;
  }

  const bool hits_shape(const int y, const int x)
  {
    return m_shape[y][x] != BLANK;
  }
private:
  int m_x;
  int m_y;
  const int m_container_dimension;
  const char** m_shape = NULL;

  static const char BLANK = ' ';
};
}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
