
#include <Arduino.h>
#include "adxl345.h"
#include "led.h"
#include "timer.h"
#include "pir.h"
#include "pwm.h"
#include "switch.h"
#include "math.h"

#define thresh 300

typedef enum stateType_enum{
  waitPress, debouncePress, waitRelease, debounceRelease
} stateType;
volatile stateType state = waitPress;
volatile bool deviceOn = false;

int main(void){
  sei();
  Serial.begin(9600);
  
  //checks for tripping the alarm
  bool motionB = false; 
  bool tooFar = false;

  initLED(); //for testing
  //initPIR(); //motion sensor
  initTimer1(); //for testing
  initADXL345(); //accelerometer
  //initPWMTimer3();
  initSwitchPB1();


  while(1) {

    switch(state){
      case waitPress:
        break;
      case debouncePress:
        delayMs(100);
        state = waitRelease;
        break;
      case waitRelease:
        break;
      case debounceRelease:
        delayMs(100);
        state = waitPress;
        break;
    }
      //bool to check if the device has been moved past the thresh value
      tooFar = (abs(getZ()) > thresh);

      //uses PIR sensor to check if any motion
      //motionB = detectMotion();
      
      Serial.print("Device on?: \t");
      Serial.println(deviceOn);
      // Serial.print("Motion: \t");
      // Serial.println(motionB);
      Serial.print("isMoved: \t");
      Serial.println(tooFar);
  
      while(deviceOn && (tooFar) /*|| motionB)*/){ // took out motion here, but will need later
        lightLED();
       // triggerAlarm(&deviceOn);
        
      }
      
      turnOffLED();
      

      delayMs(100);
        
    } 
}

 ISR(PCINT0_vect){
  if(state == waitPress){
    //Serial.println("ISR pressed");
    state = debouncePress;
  }
  else if (state == waitRelease){
    //Serial.println("ISR relaesed");
    deviceOn = !deviceOn;
    state = debounceRelease;
  }  
}   
