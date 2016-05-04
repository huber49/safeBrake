/* Non-board-specific brake-constants are stored in this .h-file.
   Version 30-04-16  
*/
#ifndef BrakeConstants_h
#define BrakeConstants_h

#include "Arduino.h"

#define BRAKE_APPLIED 10
#define BRAKE_RELEASED 11

#define TURN_RIGHT 20
#define TURN_LEFT 21

// 3.3 volt is the supply-voltage of the system.
#define SUPPLY_VOLTAGE 3.3
// VCC always should be 3.3 Volt. In case of small measurement-errors smaller values up to 3.25 Volt are also accepted. 
#define VCC_GOOD 3.25
// GND always should be 0.00 Volt. In case of small measurement-errors bigger values up to 0.05 Volt are also accepted.
#define GND_GOOD 0.05

/* FAIL_IGNORE is only necessary if you want to double-check the detected HW-Failure.
   See notes and version sketch_mar30a for more information.
*/
enum voltInterval { FAIL_GND_SHORT = 1, FAIL_VCC_SHORT, FAIL_OPEN, SWITCH_NORM_VAL, SWITCH_LOW_VAL, SWITCH_HIGH_VAL, FAIL_IGNORE};

#endif