/* Has to be .cpp and not .c
*  reason: see notes in "Notizen zur Programmentwicklung.doc"
*  Version: 30-04-16
*/
#include "brake.h"
#include "Arduino.h"
#include "brakeConstants.h"
#include "boardConstants.h"
#include "Servo.h"

static byte brakeState = 0;

/* brakeStatus - BRAKE_APPLIED 10, BRAKE_RELEASED 11
*/
byte getBrakeStatus() {
  return brakeState;
}

/* Applies the brake.
*/  
void applyBrake() {
  if(brakeState != BRAKE_APPLIED){
    brakeState = BRAKE_APPLIED;
    // control servo
    Serial.println("Stop Servo.");
    digitalWrite(INFO_LED, HIGH);
  }
}

/* Releases the brake.
*/
void releaseBrake() {
  if(brakeState != BRAKE_RELEASED){
    brakeState = BRAKE_RELEASED;
    //  control servo
    Serial.println("Start Servo.");
    digitalWrite(INFO_LED, LOW);
  }
}
/* Initialises the brake.
*/
boolean brakeInit() {
  /* Set up servo to "Brake-Applied" position */
  Serial.println("Brake-Initialization");
  // for showing, that led are working
  delay(1000);
  brakeState = BRAKE_APPLIED;
  // maybe use applyBreak();
  return true;
}