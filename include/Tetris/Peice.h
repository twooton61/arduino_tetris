#ifndef TETRIS_PEICE_H_
#define TETRIS_PEICE_H_

#include <Robo/Matrix.h>
#include <Helpers.h>
namespace Tetris
{
class Peice
{
public:
  static const int ROTATION_PHASES = 4;
  Peice(const int x, const int y, byte* const shape, const int shape_size) :
    m_x(x),
    m_y(y),
    m_rotation_phase(0),
    m_container_dimension(shape_size),
    m_shape(shape)
  {
  }

  ~Peice()
  {
  }

  GET_SET(int, x)
  GET_SET(int, y)

  int next_y(const int y_drop = 1) const
  {
    return m_y - y_drop;
  }

  int height() const
  {
    return m_container_dimension;
  }

  int width() const
  {
    return m_container_dimension;
  }

  byte row(const int y) const
  {
    // height() - 1 to flip the shape
    return m_shape[(height() + rotation_offset() - 1) - y];
  }

  bool hits_shape(const int y, const int x) const
  {
    // height() - 1 to flip the shape
    const byte col = m_shape[(height() + rotation_offset() - 1) - y];

    // if bit is set on column
    return col & (1 << (7 - x));
  }

  void rotate()
  {
    m_rotation_phase = (m_rotation_phase + 1) % ROTATION_PHASES;
  }

private:
  int m_x;
  int m_y;
  int m_rotation_phase;
  const int m_container_dimension;
  byte* const m_shape;

  int rotation_offset() const
  {
    return m_rotation_phase * m_container_dimension;
  }
};
}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
