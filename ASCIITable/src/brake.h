/* 
*  Version: 30-04-16
*/
#ifndef Brake_h
#define Brake_h

#include "Arduino.h"
#include "brakeConstants.h"

byte brakeStatus();
void applyBrake();
void releaseBrake();
boolean brakeInit();

#endif
