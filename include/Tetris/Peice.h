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
    const byte load = m_shape[y];

    Serial.print("x: ");
    Serial.println(load);
    return load & (1 << (7 - x));
  }
private:
  int m_x;
  int m_y;
  const int m_container_dimension;
  byte* const m_shape;

  static const char BLANK = ' ';
};
}  // namespace Tetris

#endif  // TETRIS_PEICE_H_
