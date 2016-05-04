#include "evaluation.h"

boolean evaluateVccSense(float measuredVcc){
  boolean vccOk = false;
  if(measuredVcc >= VCC_GOOD){
    vccOk = true;
  }
  return vccOk;
}
boolean evaluateVccSense(float measuredVcc) __attribute__ ((noinline));

boolean evaluateGndSense(float gndVoltage){
  boolean gndOk = false;
  if(gndVoltage <= GND_GOOD){
    gndOk = true;
  }
  return gndOk;
}
// to avoid, that function is optimized during compiling
boolean evaluateGndSense(float gndVoltage) __attribute__ ((noinline));

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

systemState analyseSystemState(voltInterval switchStatus1, voltInterval switchStatus2, float switch1, float switch2){
  
  systemState sysState = UNDEFINED_STATE;  //TODO: comment
  
  if((switchStatus1 == SWITCH_NORM_VAL) && (switchStatus2 == SWITCH_NORM_VAL)){
    sysState = NOTHING_PRESSED;
  }
  else if((switchStatus1 == SWITCH_LOW_VAL) && (switchStatus2 == SWITCH_HIGH_VAL)){
    sysState = APPLY_PRESSED;    
  }
  else if((switchStatus1 == SWITCH_HIGH_VAL) && (switchStatus2 == SWITCH_LOW_VAL)){
    sysState = RELEASE_PRESSED;
  }
  //HW-Failures
  else if(switchStatus1 == FAIL_VCC_SHORT)  {sysState = SHORT_VCC_C;}
  else if(switchStatus2 == FAIL_VCC_SHORT)  {sysState = SHORT_VCC_E;}
  else if(switchStatus1 == FAIL_GND_SHORT)  {sysState = SHORT_GND_D;}
  else if(switchStatus2 == FAIL_GND_SHORT)  {sysState = SHORT_GND_F;}
  else if(switchStatus1 == FAIL_OPEN)       {sysState = OPEN_RES_G;}
  else if(switchStatus2 == FAIL_OPEN)       {sysState = OPEN_RES_H;}
  else if( ((switchStatus1 == SWITCH_LOW_VAL) && (switchStatus2 == SWITCH_NORM_VAL)) ||
           ((switchStatus1 == SWITCH_NORM_VAL) && (switchStatus2 == SWITCH_LOW_VAL)) ){
    Serial.println("Detected unsynchronized-behaviour of the Switch Button --> Ignored!");
  }
  else{
      // Unknown combination of voltage-intervals - or lack of voltage interval(s)
      Serial.println("Unknown Error");
      Serial.print("   ");
      Serial.print(switch1);
      Serial.print("   ");
      Serial.println(switch2);
  }
  return sysState;
}