#ifndef TETRIS_PEICE_H_
#define TETRIS_PEICE_H_

#include <Robo/Matrix.h>
#include <Helpers.h>
namespace Tetris
{
class Peice
{
public:
  Peice(const int x, const int y, byte* const shape, const int shape_size) :
    m_x(x),
    m_y(y),
    m_container_dimension(shape_size),
    m_shape(shape)
  {
  }

  ~Peice()
  {
  }

  GET_SET(int, x)
  GET_SET(int, y)

  int next_y() const
  {
    return m_y - 1;
  }

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
    // height() - 1 to flip the shape
    const byte col = m_shape[(height() - 1) - y];

    // if bit is set on column
    return col & (1 << (7 - x));
  }
private:
  int m_x;
  int m_y;
  const int m_container_dimension;
  byte* const m_shape;
};
}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
