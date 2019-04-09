
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
//volatile bool& deviceOnRef = deviceOn;
//volatile bool* deviceOnPtr = &deviceOn;
volatile bool motionB = false; 
volatile bool tooFar = false;

int main(void){
  sei();
  Serial.begin(9600);


  initLED(); //for testing
  initPIR(); //motion sensor
  initTimer1(); //for testing
  initADXL345(); //accelerometer
  initPWMTimer3();
  initSwitchPB1();


  while(1) {
    tooFar = false;
    motionB = false;

    switch(state) {
      case waitPress:
      Serial.println("wait press");
      break;

      case debouncePress:
      Serial.println("debounce press");
      delayMs(10);
      state = waitRelease;
      break;

      case waitRelease:
      break;

      case debounceRelease:
      Serial.println("debounce relaes");
      delayMs(10);
      state = waitPress;
      break;

    }

      
      //bool to check if the device has been moved past the thresh value
      //tooFar = (abs(getZ()) > thresh);
      //uses PIR sensor to check if any motion
      //motionB = detectMotion();
      
      Serial.print("Device on: \t");
      Serial.println(deviceOn);
      // Serial.print("Motion: \t");
      // Serial.println(motionB);
      Serial.print("isMoved: \t");
      Serial.println(tooFar);
      Serial.flush();

      if(deviceOn /* && (tooFar) || motionB)*/){ // took out motion here, but will need later
        lightLED();
        triggerAlarm(&deviceOn);
        
      }
      else{
        turnOffLED();
      }

      //delayMs(100);
        
    } 
}

 ISR(PCINT0_vect){
  if(state == waitPress){
    Serial.println("ISR pressed");
    state = debouncePress;
  }
  else if (state == waitRelease){
    Serial.println("ISR relaesed");
    deviceOn = !(deviceOn);
    state = debounceRelease;
  }
}   
