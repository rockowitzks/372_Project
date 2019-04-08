
#include <Arduino.h>
#include "led.h"
#include "timer.h"
#include "adxl345.h"
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

int main(void){
  sei();
  Serial.begin(9600);
  initLED(); //for testing
  initPIR(); //motion sensor
  initTimer1(); //for testing
  initADXL345(); //accelerometer
  initPWMTimer3(); // PWM
  initSwitchPB1(); // switch



  while(1) {
    switch(state) {
      case waitPress:
      delayMs(250);
      break;

      case debouncePress:
      delayMs(250);
      break;

      case waitRelease:
      delayMs(200);
      break;

      case debounceRelease:
      delayMs(200);
      break;

      default:
      delayMs(250);
      break;
    }
       //testing PIR detector
      int z = getZ();
      motionB = detectMotion();  
      tooFar = (abs(z) > thresh);
      while((tooFar && deviceOn) || (deviceOn && motionB))  { 
        lightLED();
        triggerAlarm(&deviceOn); 
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

          case debouncePress:
          deviceOn = !deviceOn;
          state = waitRelease;
          break;

          case waitRelease:
          state = debounceRelease;
          break;

          case debounceRelease:
          state = waitPress;
          break;

          default:
          state = waitRelease;
          break;
        }
   }   



