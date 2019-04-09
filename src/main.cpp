
#include <Arduino.h>
#include "adxl345.h"
#include "led.h"
#include "timer.h"
#include "pir.h"
#include "pwm.h"
#include "switch.h"
#include "math.h"

#define thresh 300

 typedef enum {
  waitPress, debouncePress, waitRelease, debounceRelease
} states;
volatile states state = waitPress;
volatile bool deviceOn = true;
volatile bool motionB = false; 
volatile bool tooFar = false;
//volatile bool alarmOn = false;

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
      delayMs(250);
      Serial.println("debounce press left");
      state = waitRelease;
      break;

      case waitRelease:
      //delayMs(200);
      Serial.println("wait relaes");
      break;
      //more comments
      case debounceRelease:
      Serial.println("debounce relaes");
      delayMs(200);
      state = waitPress;
      break;

    }

      
      //bool to check if the device has been moved past the thresh value
      tooFar = (abs(getZ()) > thresh);
      //uses PIR sensor to check if any motion
      //motionB = detectMotion();
      
      Serial.print("Device on: \t");
      Serial.println(deviceOn);
      // Serial.print("Motion: \t");
      // Serial.println(motionB);
      Serial.print("isMoved: \t");
      Serial.println(tooFar);
      Serial.flush();

      while(deviceOn && (tooFar /*|| motionB*/)){ // took out motion here, but will need later
        Serial.println("entered checks");
        Serial.flush();
        lightLED();
        triggerAlarm(&deviceOn);
        //delayMs(100);
      }
  
      turnOffLED();
      

      delayMs(100);
        
    } 
}

 ISR(PCINT0_vect){
  if(state == waitPress){
    state = debouncePress;
  }
  else if (state == waitRelease){
    deviceOn = !deviceOn;
    state = debounceRelease;
  }
}   



