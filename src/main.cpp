/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Arduino Tetris
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/Matrix.h>
#include <Robo/IRReceiver.h>
#include <Robo/Button.h>
#include <Tetris/Board.h>

#ifdef ROBO_DEBUGGER
#include <avr8-stub.h>
#endif

Robo::Brain robo_brain;

Robo::Matrix robo_matrix(
  robo_brain,
  MATRIX_DIN_PIN(11),
  MATRIX_CS_PIN(10),
  MATRIX_CLK_PIN(12),
  MATRICIES_ON_BOARD(4)
);

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(7));

Robo::Button up_button(robo_brain, DIGITAL_IO_PIN(2));
Robo::Button down_button(robo_brain, DIGITAL_IO_PIN(3));
Robo::Button left_button(robo_brain, DIGITAL_IO_PIN(4));
Robo::Button right_button(robo_brain, DIGITAL_IO_PIN(5));

Tetris::Peice* active_peice = NULL;
Tetris::Peice* next_peice = NULL;

Tetris::Board tetris_board(robo_matrix);

bool game_over = false;

static const int TICK_INTERVAL = 300;
unsigned long last_tick = 0;

void setup()
{
  #if ROBO_DEBUGGER
  debug_init();
  #endif

  randomSeed(analogRead(0));

  Log::init();

  robo_brain.setup();

  byte screen[] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111111
  };

  tetris_board.draw(screen, sizeof(screen), Tetris::Board::ROWS);
}

void loop()
{
  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  if (millis() < last_tick + TICK_INTERVAL){
    return;
  }
  last_tick += TICK_INTERVAL;

  if (game_over) {
    Serial.println("Game Over");

    const byte sad_face[] = {
      0b00000000,
      0b00100100,
      0b00100100,
      0b00000000,
      0b00111100,
      0b01000010,
      0b01000010,
      0b00000000
    };

    tetris_board.draw(sad_face, sizeof(sad_face), Tetris::Board::ROWS);

    delay(100000);
    return;
  }

  if (active_peice == NULL) {
    if (next_peice != NULL) {
      tetris_board.clear_peice_unbounded(*next_peice);
      active_peice = next_peice;
      next_peice = NULL;
    }
    else {
      active_peice = tetris_board.generate_new_peice(0, Tetris::Board::ROWS);
    }
  }

  if (next_peice == NULL) {
    next_peice = tetris_board.generate_new_peice(0, Tetris::Board::ROWS + 2);

    tetris_board.draw_peice_unbounded(*next_peice);
  }

  if (active_peice != NULL) {
    tetris_board.clear_peice(*active_peice);

    if (right_button.is_pressed()) {
      active_peice->move_x(1);
    }

    if (active_peice->x() != 0 && left_button.is_pressed()) {
      active_peice->move_x(-1);
    }

    bool drop_more = true;
    if (down_button.is_pressed()) {
      int y_drop = 1;
      while (active_peice->y() - y_drop >= 0 && !tetris_board.peice_will_collide_with_dot_pile(*active_peice, y_drop)){
        y_drop++;
      }

      active_peice->y(active_peice->y() - (y_drop - 1));

      drop_more = false;
    }

    if (up_button.is_pressed()) {
      active_peice->rotate();
    }

    bool peice_commited_to_dot_pile = false;
    if (active_peice->y() > 0){
      if (tetris_board.peice_will_collide_with_dot_pile(*active_peice, 1)){

        if (active_peice->y() >= Tetris::Board::ROWS - 1) {
          game_over = true;
        }

        tetris_board.commit_peice_to_dot_pile(*active_peice);
        peice_commited_to_dot_pile = true;
      }
      else if (drop_more) {
        active_peice->move_y(-1);
      }
    }
    else {
      // row hit bottom
      tetris_board.commit_peice_to_dot_pile(*active_peice);
      peice_commited_to_dot_pile = true;
    }

    if (peice_commited_to_dot_pile) {
      delete active_peice;
      active_peice = NULL;

      tetris_board.compact_dot_pile();
      tetris_board.clear_board();
    }
    else {
      tetris_board.draw_peice(*active_peice);
    }
  }

  tetris_board.draw_dot_pile();
}

