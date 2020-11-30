#include <Arduino.h>
#include <Robo/Matrix.h>
namespace Robo {
Matrix::Matrix(Brain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board) :
    Robo::AbstractPart(robo_brain, "Max Matrix"),
    m_din_pin(din_pin),
    m_cs_load_pin(cs_load_pin),
    m_clk_pin(clk_pin),
    m_matricies_on_board(matricies_on_board),
    m_max_rows(DIM),
    m_max_cols(DIM * matricies_on_board),
    m_max_matrix(din_pin, cs_load_pin, clk_pin, matricies_on_board)
{
}

void Matrix::setup() {
    m_max_matrix.init();
    m_max_matrix.setIntensity(0);
}


void Matrix::clear_current() {
    m_max_matrix.setDot(current_matrix_x, current_matrix_y, 0);
}

void Matrix::move_x(const int movement)
{
    clear_current();

    int new_x = (current_matrix_x + movement);
    if (new_x < 0) {
        new_x = 0;
    }
    else if (new_x >= m_max_cols) {
        new_x = m_max_cols-1;
    }

    Serial.print("x: ");
    Serial.println(new_x);

    current_matrix_x = new_x;

    render();
}

void Matrix::move_y(const int movement)
{
    clear_current();

    int new_y = (current_matrix_y + movement);
    if (new_y < 0) {
        new_y = 0;
    }
    else if (new_y >= m_max_rows) {
        new_y = m_max_rows-1;
    }

    Serial.print("y: ");
    Serial.println(new_y);

    current_matrix_y = new_y;

    render();
}

void Matrix::render()
{
    m_max_matrix.setDot(current_matrix_x, current_matrix_y, 1);
}
}