#ifndef ROBO_MATRIX_H
#define ROBO_MATRIX_H

#include <Arduino.h>
#include <MaxMatrix.h>
#include <AbstractRoboPart.h>

class RoboMatrix : AbstractRoboPart {
    static const int DIM = 8;
    const int m_din_pin;
    const int m_cs_load_pin;
    const int m_clk_pin;
    const int m_matricies_on_board;
    const int m_max_rows;
    const int m_max_cols;

    MaxMatrix m_max_matrix;
    int current_matrix_x = 0;
    int current_matrix_y = 0;

    public:

    RoboMatrix(RoboBrain& robo_brain, const int din_pin, const int cs_load_pin, const int clk_pin, const int matricies_on_board);

    void setup();
    void clear_current();
    void move_x(const int movement);
    void move_y(const int movement);
    void render();
};

#endif