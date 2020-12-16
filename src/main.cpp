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
#include <Tetris/Game.h>
#include <Tetris/IPeice.h>
#include <Tetris/JPeice.h>
#include <Tetris/LPeice.h>
#include <Tetris/SPeice.h>
#include <Tetris/SquarePeice.h>
#include <Tetris/TPeice.h>
#include <Tetris/ZPeice.h>

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


int period = 300;
unsigned long time_now = 0;

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

  tetris_board.draw(screen, sizeof(screen), Tetris::Board::BOARD_ROWS);
}

void loop()
{
  if (game_over) {
    Serial.println("Game Over");

    byte sad_face[] = {
      0b00000000,
      0b00100100,
      0b00100100,
      0b00000000,
      0b00111100,
      0b01000010,
      0b01000010,
      0b00000000
    };

    tetris_board.draw(sad_face, sizeof(sad_face), Tetris::Board::BOARD_ROWS);

    delay(1000);
    return;
  }

  if (active_peice == NULL) {
    if (next_peice != NULL) {
      tetris_board.clear_peice_unbounded(*next_peice);
      active_peice = next_peice;
      next_peice = NULL;
    }
    else {
      static const int TOTAL_POSSIBLE_PEICES = 7;
      const int peice_index = random(0, TOTAL_POSSIBLE_PEICES - 1);
      switch (peice_index){
        case 0:
          active_peice = new Tetris::SquarePeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 1:
          active_peice = new Tetris::IPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 2:
          active_peice = new Tetris::JPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 3:
          active_peice = new Tetris::LPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 4:
          active_peice = new Tetris::SPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 5:
          active_peice = new Tetris::TPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
        case 6:
          active_peice = new Tetris::ZPeice(0, Tetris::Board:: BOARD_ROWS);
          break;
      }
    }
  }

  if (next_peice == NULL) {
    static const int TOTAL_POSSIBLE_PEICES = 7;
    const int peice_index = random(0, TOTAL_POSSIBLE_PEICES - 1);
    switch (peice_index){
      case 0:
        next_peice = new Tetris::SquarePeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 1:
        next_peice = new Tetris::IPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 2:
        next_peice = new Tetris::JPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 3:
        next_peice = new Tetris::LPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 4:
        next_peice = new Tetris::SPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 5:
        next_peice = new Tetris::TPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
      case 6:
        next_peice = new Tetris::ZPeice(0, Tetris::Board:: BOARD_ROWS + 2);
        break;
    }

    tetris_board.draw_peice_unbounded(*next_peice);
  }

  Tetris::Peice& peice = *active_peice;

  if (robo_ir_receiver.detect_signal()) {
    Log::println("signal detected");

    robo_ir_receiver.resume();
  }

  if (millis() >= time_now + period){
    time_now += period;

    if (active_peice != NULL) {
      tetris_board.clear_peice(*active_peice);

      if (right_button.is_pressed()) {
        active_peice->x(active_peice->x() + 1);
      }

      if (active_peice->x() != 0 && left_button.is_pressed()) {
        active_peice->x(active_peice->x() - 1);
      }

      bool drop_more = true;
      if (down_button.is_pressed()) {
        int y_drop = 1;
        while (!tetris_board.peice_will_collide_with_dot_pile(peice, y_drop)){
          y_drop++;
        }

        active_peice->y(active_peice->y() - (y_drop - 1));

        drop_more = false;
      }

      if (up_button.is_pressed()) {
        active_peice->rotate();
      }

      bool peice_commited = false;
      if (active_peice->y() > 0){
        if (tetris_board.peice_will_collide_with_dot_pile(peice, 1)){

          if (active_peice->y() >= Tetris::Board:: BOARD_ROWS - 1) {
            game_over = true;
          }

          tetris_board.commit_peice_to_dot_pile(&active_peice);

          delete active_peice;
          active_peice = NULL;
                  peice_commited = true;
        }
        else if (drop_more) {
          active_peice->y(active_peice->y() - 1);
        }
      }
      else {
        // row hit bottom
        tetris_board.commit_peice_to_dot_pile(&active_peice);
        peice_commited = true;
          delete active_peice;
          active_peice = NULL;
      }

      if (!peice_commited) {
        tetris_board.draw_peice(*active_peice);
      }
    }

    tetris_board.draw_dot_pile();
  }
}

