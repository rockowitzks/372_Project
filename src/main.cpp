
#include <Arduino.h>
#include "adxl345.h"
#include "led.h"
#include "timer.h"
#include "pir.h"
#include "pwm.h"
#include "switch.h"

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
    // may not need the next 3 lines
    tooFar = false;
    motionB = false;

    switch(state) {
      case waitPress:
      Serial.println("wait press");
      //delayMs(250);
      break;

      case debouncePress:
      Serial.println("debounce press");
      delayMs(250);
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

      default:
      delayMs(250);
      state = waitPress;
      break;
    }
      
      //testing PIR detector
      int z = getZ();
      motionB = detectMotion();
      
      tooFar = (abs(z) > thresh);
      while(deviceOn && (tooFar || motionB)){ // took out motion here, but will need later
        lightLED();
        triggerAlarm(&deviceOn);
        //delayMs(100);
      }
  
      turnOffLED();
      

      delayMs(100);
        
    } 
}

 ISR(PCINT0_vect){
       switch(state) {
          case waitPress:
          state = debouncePress;
          break;

          case waitRelease:
          deviceOn = !deviceOn;
          state = debounceRelease;
          break;
        }
   }   



