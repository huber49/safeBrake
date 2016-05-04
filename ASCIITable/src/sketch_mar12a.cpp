/* Version: 04-05-16
   
   There are still some Error-Messages because of unexpected measurement-values,
   if switch is in the "unsynchronized" position.
*/

#include "Servo.h"
#include "brake.h"
#include "servoControl.h"
#include "constants.h"
#include "evaluation.h"

/********************************************************* 
**********************************************************
**    Variable declarations initialization / resets     **
**********************************************************
*********************************************************/

Servo brakeSimulator;
byte brakeStatus;

/********************************************************* 
**********************************************************
**                 Method declarations                  **
**********************************************************
*********************************************************/


// Read Values at ADCs and converts into Volt.
float readVccSense(){
  return analogRead(VCC_ADC) * (SUPPLY_VOLTAGE / ADC_MAX_VALUE);
}
float readGndSense(){
  return analogRead(GND_ADC)*(SUPPLY_VOLTAGE / ADC_MAX_VALUE);
}
float readSwitchSense1(){
  return analogRead(SWITCH_1_ADC) * (SUPPLY_VOLTAGE / ADC_MAX_VALUE);
}
float readSwitchSense2(){
  return analogRead(SWITCH_2_ADC) * (SUPPLY_VOLTAGE / ADC_MAX_VALUE);
}

// Supporting function for printing simple error-messages.
void reportError(String errorType){
  Serial.println(errorType);
  digitalWrite(ERROR_LED, HIGH);
}

// Supporting function for printing messages, if switch is not in neutral position.
void reportSwitchPress(String pressedType){
  Serial.println(pressedType);
}

/********************************************************* 
**********************************************************
**                      setup()                         **
**********************************************************
*********************************************************/

void setup() {
  brakeSimulator.attach(SERVO_PIN);           //Attach Servo to PIN 9~
  
  pinMode(LED, OUTPUT);                       // Initializing led-pin as an output.
  pinMode(ERROR_LED, OUTPUT);                 // Initializing led-pin as an output.
  pinMode(INFO_LED, OUTPUT);                  // Initializing led-pin as an output.
  
  analogReadResolution(ADC_READ_RESOLUTION);  // Sets the size (in bits) of the value returned by analogRead(). 
  
  Serial.begin(115200);                       // Sets the data rate for communication with the computer - 115200 is one of the default rates.       
  
  // Checks if brake-initialization was successful
  if (brakeInit() != true) {
    Serial.println("Can't initialise brake - stopping.");
    while(1);
  }
  else{
    // Initialization successful -> brake applied!
    digitalWrite(ERROR_LED, LOW);
  }
}

/********************************************************* 
**********************************************************
**                       loop()                         **
**********************************************************
*********************************************************/

void loop() {
  
  /********************************************************* 
  **    Variable declarations initialization / resets     **
  *********************************************************/
 
  float vccSense = 0;             // vccSense - measured VCC-control voltage 
  float gndSense = 0;             // gndSense - measured GND-control voltage
  float switch1 = 0;              // switch1 - measured voltage of first switch-part
  float switch2 = 0;              // switch2 - measured voltage of second switch-part
  boolean vccStatusOk = 0;        // vccStatusOk - true, if there is no short or opening in the signal circuit
  boolean gndStatusOk = 0;        // gndStatusOk - true, if there is no short or opening in the signal circuit
  voltInterval switchStatus1;     // Indicates, in which range the first measured switch-value was.
  voltInterval switchStatus2;     // Indicates in which range the second measured switch-value was.
  int servoPos = 0;               // position of servo - [0,180]
  systemState sysState;
  
  /********************************************************* 
  **              Methods / "Working Part"                **
  *********************************************************/
  
  // Switch led on and off, to signalize that the programme is running.
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
  
  vccSense = readVccSense();
  gndSense = readGndSense();
  switch1 = readSwitchSense1();
  switch2 = readSwitchSense2();
  
  vccStatusOk = evaluateVccSense(vccSense);
  gndStatusOk = evaluateGndSense(gndSense);
  switchStatus1 = evaluateSwitch(switch1);
  switchStatus2 = evaluateSwitch(switch2);

  if(!vccStatusOk){reportError("Error: VCC");}
  if(!gndStatusOk){reportError("Error: GND");}
  
  if(vccStatusOk && gndStatusOk){
    // Reasons Brake-/Switch/Circuit-State based on measured ADC-values and defined voltage intervals.
    sysState = analyseSystemState(switchStatus1, switchStatus2, switch1, switch2);
  }
  
  //applySystemState(sysState)      //TODO : find better name for function!
  //!!!Achtung gndOK und vccOK noch mit berücksichtigen
  switch (sysState){
    case APPLY_PRESSED:
      applyBrake();
      break;
    case RELEASE_PRESSED:
      releaseBrake();
      break;
    case SHORT_VCC_C:
      reportError("Short VCC -> C.");
      break;
    case SHORT_VCC_E:
      reportError("Short VCC -> E.");
      break;
    case SHORT_GND_D:
      reportError("Short GND -> D.");
      break;
    case SHORT_GND_F:
      reportError("Short GND -> F.");
      break;
    case OPEN_RES_G:
      reportError("Open res @ G.");
      break;
    case OPEN_RES_H:
      reportError("Open res @ H.");
      break;      
  }
        
  brakeStatus = getBrakeStatus();
  
  servoPos = getServoPos(brakeStatus);
  
  if((servoPos >= 0) && (servoPos <= 180)){    // check value, before passing it to a library function! MISRA-Dir. 4.11
    brakeSimulator.write(servoPos);
  } 
 }