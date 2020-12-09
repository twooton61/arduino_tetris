#ifndef ROBO_MATRIX_H_
#define ROBO_MATRIX_H_

#include <Arduino.h>
#include <LedControl.h>
#include <Robo/AbstractPart.h>

#define MATRIX_DIN_PIN(pin) pin
#define MATRIX_CLK_PIN(pin) pin
#define MATRIX_CS_PIN(pin) pin
#define MATRICIES_ON_BOARD(pin) pin
namespace Robo {

class Matrix : AbstractPart
{
public:
  Matrix(Brain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board);

  void setup() override;
  void clear();
  void set_led_on(const int x, const int y, const bool on);
private:
  LedControl m_max_matrix;
  static const int m_min_x = 1;
  static const int m_min_y = 1;
  const int m_max_x;
  const int m_max_y;
  const int m_matricies_on_board;
};

}  // namespace Robo

#endif  // ROBO_MATRIX_H_
