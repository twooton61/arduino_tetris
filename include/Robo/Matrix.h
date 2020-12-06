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
class Matrix : AbstractPart {
    LedControl m_max_matrix;
    int m_current_matrix_x;
    int m_current_matrix_y;

    public:

    Matrix(Brain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board);

    void setup() override;
    void clear_current();
    void move_x(const int movement);
    void move_y(const int movement);
    void render();
    void set_on_led(const int x, const int y, const bool on);
};
}  // namespace Robo

#endif  // ROBO_MATRIX_H_
