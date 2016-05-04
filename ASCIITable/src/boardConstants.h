#ifndef BoardConstants_h
#define BoardConstants_h

#include "Arduino.h"

/* id of the board-integrated led.
*  shows that we main loop is running
*/
#define LED 13

/* id of the error led.
*  shows that there is a hw-failure.
*/
#define ERROR_LED 12

/* id of the info led.
*  indicates brake-state (applied or released)
*/
#define INFO_LED 11


// id of ADC input-pin for the vcc-sense-measurement
#define VCC_ADC A3
// id of ADC input-pin for the gnd-sense-measurement
#define GND_ADC A0
// id of ADC input-pin for first switch-measurement
#define SWITCH_1_ADC A1
// id of ADC input-pin for second switch-measurement
#define SWITCH_2_ADC A2
// highest resolution for ADC-reading to have exact voltage measurement-values
#define ADC_READ_RESOLUTION 12
// 4095 if ADC_READ_RESOLUTION is 12 - 4095 is the maximum value at the Input-ADC, representing 3.3 volt
#define ADC_MAX_VALUE (pow(2, ADC_READ_RESOLUTION) - 1)

#endif