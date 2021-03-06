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
  m_max_y(LEDS_PER_MATRIX_ROW * matricies_on_board),
  m_matricies_on_board(matricies_on_board)
{
}

void Matrix::setup()
{
  for (int i = 0; i < m_matricies_on_board; ++i) {
    m_max_matrix.shutdown(i, false);
    m_max_matrix.setIntensity(i, 5);
    m_max_matrix.clearDisplay(i);
  }
}

void Matrix::clear() {
  for (int i = 0; i < m_matricies_on_board; ++i) {
    m_max_matrix.clearDisplay(i);
  }
}
void Matrix::set_row_on(const int y, const bool on)
{
  const int board_index = get_board_index(y);
  const int col_index = get_col_index(y);

  m_max_matrix.setColumn(board_index, col_index, 0b11111111);
}

void Matrix::set_led_on(const int x, const int y, const bool on)
{
  // the boards are meant to be laid down sideways, with the 0 matrix being the right most and 3 being the left most
  // this also that rows and cols are flipped and are 0 indexed
  // if laid on it's side 0,0 is the top left of each seperate matrix

  const int board_index = get_board_index(y);
  const int col_index = get_col_index(y);
  const int row_index = get_row_index(x);

  // Log::println(String("set_led_on x: ") + String(x) + String(" True y: ") + String(row_index) + String(" on board: ") + String(board_index));
  // Log::println(String("set_led_on y: ") + String(y) + String(" True x: ") + String(col_index) + String(" on board: ") + String(board_index));

  m_max_matrix.setLed(board_index, row_index, col_index, on);
}

const int Matrix::get_board_index(const int y) const
{
  return y / LEDS_PER_MATRIX_COL;
}
const int Matrix::get_col_index(const int y) const
{
  return (LEDS_PER_MATRIX_COL - (y % LEDS_PER_MATRIX_COL)) - 1;
}

const int Matrix::get_row_index(const int x) const
{
  return (LEDS_PER_MATRIX_ROW - x) - 1;
}
}  // namespace Robo
