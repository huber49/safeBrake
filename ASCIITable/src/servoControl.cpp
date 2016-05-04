#include "servoControl.h"

static int servoPos = START_POS;
byte simulatorDirection = TURN_RIGHT;

int getServoPos(byte brakeState){
  
  // change direction if servo is at it's limits
  if(servoPos == END_POS){
    simulatorDirection = TURN_LEFT;
  }
  if(servoPos == START_POS){
    simulatorDirection = TURN_RIGHT;
  }
  
  // change position, according to brakestate
  if(brakeState == BRAKE_RELEASED){
    if(simulatorDirection == TURN_RIGHT){
      servoPos += 1;
    }
    else if(simulatorDirection == TURN_LEFT){
      servoPos -= 1;
    }
  }
  else if(brakeState == BRAKE_APPLIED){
    servoPos = START_POS;
  }
  else{
    Serial.print("Error: BrakeState-Evaluation!");
  }
  
  Serial.println(servoPos);
  
  return servoPos;
}