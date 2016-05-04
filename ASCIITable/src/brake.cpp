/* Has to be .cpp and not .c
*  reason: see notes in "Notizen zur Programmentwicklung.doc"
*  Version: 30-04-16
*/
#include "brake.h"
#include "constants.h"

static byte brakeState = 0;

byte getBrakeStatus() {
  return brakeState;
}

void applyBrake() {
  if(brakeState != BRAKE_APPLIED){
    brakeState = BRAKE_APPLIED;
    // control servo
    Serial.println("Stop Servo.");
    digitalWrite(INFO_LED, HIGH);
  }
}

void releaseBrake() {
  if(brakeState != BRAKE_RELEASED){
    brakeState = BRAKE_RELEASED;
    //  control servo
    Serial.println("Start Servo.");
    digitalWrite(INFO_LED, LOW);
  }
}

boolean brakeInit() {
  /* Set up servo to "Brake-Applied" position */
  Serial.println("Brake-Initialization");
  // for showing, that led are working
  delay(1000);
  brakeState = BRAKE_APPLIED;
  // maybe use applyBreak();
  return true;
}