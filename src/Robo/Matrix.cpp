#include <Arduino.h>
#include <Robo/Matrix.h>
#include <Helpers.h>

namespace Robo {
const int LEDS_PER_MATRIX_ROW = 8;
const int LEDS_PER_MATRIX_COL = 8;

Matrix::Matrix(Brain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board) :
    AbstractPart(robo_brain, "Max Matrix"),
    m_max_matrix(din_pin, clk_pin, cs_load_pin, matricies_on_board),
    m_max_x(LEDS_PER_MATRIX_COL),
    m_max_y(LEDS_PER_MATRIX_ROW * matricies_on_board)
{
}

void Matrix::setup()
{
    m_max_matrix.shutdown(0, false);
    m_max_matrix.shutdown(1, false);
    m_max_matrix.shutdown(2, false);
    m_max_matrix.shutdown(3, false);
    m_max_matrix.setIntensity(0, 5);
    m_max_matrix.setIntensity(1, 5);
    m_max_matrix.setIntensity(2, 5);
    m_max_matrix.setIntensity(3, 5);
    m_max_matrix.clearDisplay(0);
    m_max_matrix.clearDisplay(1);
    m_max_matrix.clearDisplay(2);
    m_max_matrix.clearDisplay(3);



}

void Matrix::clear() {
    m_max_matrix.clearDisplay(0);
    m_max_matrix.clearDisplay(1);
    m_max_matrix.clearDisplay(2);
    m_max_matrix.clearDisplay(3);
}


void Matrix::set_led_on(const int x, const int y, const bool on)
{
    const int true_board = (y - 1) / LEDS_PER_MATRIX_COL;
    const int true_x = (true_board * 8) + (8 - y);
    const int true_y = 8 - x;
    // Log::println(String("x: ") + String(x) + String(" True x: ") + String(true_x));
    // Log::println(String("y: ") + String(y) + String(" True y: ") + String(true_y));
    // Log::println(String("True board: ") + true_board);

    m_max_matrix.setLed(true_board, true_y, true_x, on);
}

}  // namespace Robo
