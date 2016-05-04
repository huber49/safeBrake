/* Version: 30-04-16
   
   There are still some Error-Messages because of unexpected measurement-values,
   if switch is in the "unsynchronized" position.
*/

#include "Arduino.h"
#include "brake.h"
#include "brakeConstants.h"
#include "boardConstants.h"

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

/* Checks, if supply-voltage is ok.
   true - if there are no HW-failures in circuit.
*/
boolean evaluateVccSense(float measuredVcc){
  boolean vccOk;
  if(measuredVcc >= VCC_GOOD){ vccOk = true;}
  else{vccOk = false;}
  return vccOk;
}
// to avoid, that function is optimized during compiling
boolean evaluateVccSense(float measuredVcc) __attribute__ ((noinline));

boolean testfunc(){
  return false;
}

/* Checks, if gnd-voltage is ok.
   true - if there are no HW-failures in circuit.
*/
boolean evaluateGndSense(float gndVoltage){
  boolean gndOk;
  if(gndVoltage <= GND_GOOD){ gndOk = true;}
  else{gndOk = false;}
  return gndOk;
}
// to avoid, that function is optimized during compiling
boolean evaluateGndSense(float gndVoltage) __attribute__ ((noinline));

/*
  only the return-status 1, 7 and 13 (and maybe 2) are relevant for the detection and identification of hardware-failures
  the other statuses are good to know if you want to double-check a certain hw-failure-detection, but they
  are not used in this version of the algorithm (maybe i can use the on the second board in an other algorithm)
  
  return-status 2, 5 and 11 are rekevant for the evaluation of the pressed-status of the switch-button.

  Note/TODO: Maybe it is better / nicer to use a map in this function, to map a voltage to an interval, that can be mapped to a status!
*/
voltInterval evaluateSwitch(float voltage){
  voltInterval returnStatus; //check, if NULL is ok as default - what happens if NULL is returned?
  if((voltage >= 0.00) && (voltage <= 0.03)){returnStatus = FAIL_GND_SHORT;}
  else if((voltage >= 0.29) && (voltage <= 0.42)){returnStatus = SWITCH_LOW_VAL;}
  else if((voltage >= 0.69) && (voltage <= 0.73)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 0.81) && (voltage <= 0.86)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 1.03) && (voltage <= 1.18)){returnStatus = SWITCH_NORM_VAL;}
  else if((voltage >= 1.58) && (voltage <= 1.68)){returnStatus = FAIL_OPEN;}
  else if((voltage >= 1.86) && (voltage <= 1.91)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 2.23) && (voltage <= 2.28)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 2.43) && (voltage <= 2.48)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 2.49) && (voltage <= 2.61)){returnStatus = SWITCH_HIGH_VAL;}
  else if((voltage >= 2.80) && (voltage <= 2.84)){returnStatus = FAIL_IGNORE;}
  else if((voltage >= 2.98) && (voltage <= 3.30)){returnStatus = FAIL_VCC_SHORT;}
  else {
    Serial.print("evaluateError!");
    Serial.print("   ");
    Serial.println(voltage);    
  }
  return returnStatus;
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

void setup() {
  // Initializing led-pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(INFO_LED, OUTPUT);
  // Sets the size (in bits) of the value returned by analogRead().
  analogReadResolution(ADC_READ_RESOLUTION);
  // Sets the data rate for communication with the computer - 115200 is one of the default rates.
  Serial.begin(115200);
  // Checks if brake-initialization was successful
  if (brakeInit() != true) {
    Serial.println("Can't initialise brake - stopping.");
    while(1);
  }
  else{
    // Initialization successful -> brake applied!
    // Serial.println(brakeStatus());
    digitalWrite(ERROR_LED, LOW);
  }
}

void loop() {
  
  /*********************************************** 
    Variable declarations initialization / resets
  ***********************************************/
  
  // vccSense - measured VCC-control voltage 
  float vccSense = 0;
  // gndSense - measured GND-control voltage
  float gndSense = 0;
  // switch1 - measured voltage of first switch-part
  float switch1 = 0;
  // switch2 - measured voltage of second switch-part
  float switch2 = 0;
  // vccStatusOk - true, if there is no short or opening in the signal circuit
  boolean vccStatusOk = 0;
  // gndStatusOk - true, if there is no short or opening in the signal circuit
  boolean gndStatusOk = 0;
  // Indicates, in which range the first measured switch-value was.
  voltInterval switchStatus1;
  // Indicates in which range the second measured switch-value was.
  voltInterval switchStatus2;
  
  /**************************
    Methods / "Working-Part"
  **************************/
  
  // Switch led on and off, to signalize that the programme is running.
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
  
  // Read ADC-Input.
  vccSense = readVccSense();
  gndSense = readGndSense();
  switch1 = readSwitchSense1();
  switch2 = readSwitchSense2();
  
  // Check, if "basic" (no switch) circuit is ok.   
  vccStatusOk = evaluateVccSense(vccSense);
  gndStatusOk = evaluateGndSense(gndSense);
  
  /* Two of the following values: 
     FAIL_GND_SHORT, FAIL_VCC_SHORT, FAIL_OPEN, SWITCH_NORM_VAL, SWITCH_LOW_VAL, SWITCH_HIGH_VAL, FAIL_IGNORE
     Indicate position of switch and possible HW-Failures. 
  */ 
  switchStatus1 = evaluateSwitch(switch1);
  switchStatus2 = evaluateSwitch(switch2);

  if(!vccStatusOk){reportError("Error: VCC");}
  if(!gndStatusOk){reportError("Error: GND");}
  
  // Reasons Brake-/Switch/Circuit-State based on measured ADC-values and defined voltage intervals.
  if(vccStatusOk && gndStatusOk){
    if((switchStatus1 == SWITCH_NORM_VAL) && (switchStatus2 == SWITCH_NORM_VAL)){/*nothing pressed*/}
    else if((switchStatus1 == SWITCH_LOW_VAL) && (switchStatus2 == SWITCH_HIGH_VAL)){
      reportSwitchPress("Apply pressed.");
      applyBrake();
    }
    else if((switchStatus1 == SWITCH_HIGH_VAL) && (switchStatus2 == SWITCH_LOW_VAL)){
      reportSwitchPress("Release pressed.");
      releaseBrake();
    }
    //HW-Failures
    else if(switchStatus1 == FAIL_VCC_SHORT){reportError("Short VCC -> C.");}
    else if(switchStatus2 == FAIL_VCC_SHORT){reportError("Short VCC -> E.");}
    else if(switchStatus1 == FAIL_GND_SHORT){reportError("Short GND -> D.");}
    else if(switchStatus2 == FAIL_GND_SHORT){reportError("Short GND -> F.");}
    else if(switchStatus1 == FAIL_OPEN){reportError("Open res @ G.");}
    else if(switchStatus2 == FAIL_OPEN){reportError("Open res @ H.");}
    else if( ((switchStatus1 == SWITCH_LOW_VAL) && (switchStatus2 == SWITCH_NORM_VAL)) ||
             ((switchStatus1 == SWITCH_NORM_VAL) && (switchStatus2 == SWITCH_LOW_VAL)) ){
      Serial.println("Detected unsynchronized-behaviour of the Switch Button --> Ignored!");
    }
    // Unknown combination of voltage-intervals - or lack of voltage interval(s)
    else{Serial.println("Unknown Error");
        Serial.print("   ");
        Serial.print(switch1);
        Serial.print("   ");
        Serial.println(switch2);}
  }
}
