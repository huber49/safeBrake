#ifndef Constants_h
#define Constants_h

/* id of pwm-pin, to which the servo is connected to
*/
#define SERVO_PIN 9
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

enum systemState { UNDEFINED_STATE, NOTHING_PRESSED, APPLY_PRESSED, RELEASE_PRESSED, SHORT_VCC_C, SHORT_VCC_E, SHORT_GND_D, SHORT_GND_F, OPEN_RES_G, OPEN_RES_H};

#endif