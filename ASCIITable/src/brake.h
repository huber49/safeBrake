/* 
*  Version: 30-04-16
*/
#ifndef Brake_h
#define Brake_h

#include "Arduino.h"

#define BRAKE_APPLIED 10
#define BRAKE_RELEASED 11

/* brakeStatus - BRAKE_APPLIED 10, BRAKE_RELEASED 11
*/
byte getBrakeStatus();

/* Applies the brake.
*/  
void applyBrake();

/* Releases the brake.
*/
void releaseBrake();

/* Initialises the brake.
*/
boolean brakeInit();

#endif
