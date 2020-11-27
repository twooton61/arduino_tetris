/*
  Arduino Tetris
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Arduino Tetris
*/

#include <Arduino.h>
#include <Helpers.h>
#include <RoboBrain.h>
#include <RoboMatrix.h>
#include <RoboIRReceiver.h>

RoboBrain robo_brain;

const int max_matricies_on_board = 2;
RoboMatrix robo_matrix(robo_brain, DIGITAL_IO_PIN(11), DIGITAL_IO_PIN(10), DIGITAL_IO_PIN(13), max_matricies_on_board);

RoboIRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(7));

void setup()
{
  Serial.begin(9600);

  robo_brain.setup();
}

void loop()
{
  if (robo_ir_receiver.detect_signal()) {
    const RoboIRReceiver::IRCode ir_code = robo_ir_receiver.get_ir_code();
    Serial.print("IR code: ");
    Serial.println(ir_code);

    switch(ir_code) {
      case RoboIRReceiver::IR_CODE_LEFT:
        robo_matrix.move_x(-1);
        break;
      case RoboIRReceiver::IR_CODE_RIGHT:
        robo_matrix.move_x(1);
        break;
      case RoboIRReceiver::IR_CODE_UP:
        robo_matrix.move_y(-1);
        break;
      case RoboIRReceiver::IR_CODE_DOWN:
        robo_matrix.move_y(1);
        break;
      default:
        robo_matrix.move_x(1);
        break;
    }
    robo_ir_receiver.resume();
  }

  delay(500);
}
