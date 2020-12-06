#include <Arduino.h>
#include <Robo/Matrix.h>
#include <Helpers.h>

namespace Robo {
    const int LEDS_PER_MATRIX_ROW = 8;
    const int LEDS_PER_MATRIX_COL = 8;
    const int MIN_X = 1;
    const int MAX_X = 8;
    const int MIN_Y = 1;
    const int MAX_Y = 32;
Matrix::Matrix(Brain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board) :
    AbstractPart(robo_brain, "Max Matrix"),
    m_max_matrix(din_pin, clk_pin, cs_load_pin, matricies_on_board),
    m_current_matrix_x(1),
    m_current_matrix_y(1)
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

    set_on_led(m_current_matrix_x, m_current_matrix_y, true);
}

void Matrix::clear_current()
{

}

void Matrix::move_x(const int movement)
{
    int new_x = (m_current_matrix_x + movement);

    Log::print("x: ");
    Log::println(String(new_x));

    set_on_led(m_current_matrix_x, m_current_matrix_y, false);

    m_current_matrix_x = new_x;

    set_on_led(m_current_matrix_x, m_current_matrix_y, true);
}

void Matrix::move_y(const int movement)
{
    int new_y = (m_current_matrix_y + movement);

    Log::print("y: ");
    Log::println(String(new_y));

    set_on_led(m_current_matrix_x, m_current_matrix_y, false);

    m_current_matrix_y = new_y;

    set_on_led(m_current_matrix_x, m_current_matrix_y, true);

}

void Matrix::render()
{

}

void Matrix::set_on_led(const int x, const int y, const bool on)
{
    const int true_x = 8 - y;
    const int true_y = 8 - x;
    const int true_board = (y - 1) / LEDS_PER_MATRIX_COL;
    Log::println(String("x: ") + String(x) + String(" True x: ") + String(true_x));
    Log::println(String("y: ") + String(y) + String(" True y: ") + String(true_y));
    Log::println(String("True board: ") + true_board);

    // m_max_matrix.setLed(2, 4, 7, on);
    m_max_matrix.setLed(true_board, true_y, (true_board * 8) + true_x, on);
}

}  // namespace Robo
