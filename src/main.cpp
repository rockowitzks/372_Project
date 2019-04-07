
#include <Arduino.h>
#include "led.h"
#include "timer.h"
#include "pir.h"


 typedef enum {
  waitPress, debouncePress, waitRelease, debounceRelease
} states;
volatile states state = waitPress;
volatile bool deviceOn = true;
volatile bool motionB = false; 

int main(void){
  sei();
  Serial.begin(9600);
  initLED();
  Serial.println("began initializing PIR");
  Serial.flush();
  initPIR();
  Serial.println("finished initializing PIR");
  Serial.flush();
  initTimer1();


/*
  while(1){
    //testing PIR detector
    bool motion = detectMotion();
    Serial.println(motion);
    if(motion){
      lightLED();
    }
    else{
      turnOffLED();
    }

    delayMs(500);
  }
   */

    while(1) {
      // may not need the next 3 lines
       motionB = detectMotion();
       Serial.println(motionB);
       Serial.flush();

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
    } 
}

 ISR(PCINT0_vect){
       motionB = detectMotion();
       Serial.println(motionB);
       Serial.flush();
       switch(state) {
          case waitPress:
          state = debouncePress;
          break;

          case debouncePress:
          deviceOn = !deviceOn;
              if(deviceOn) {
                // operate normally
                if(motionB){
                lightLED();
            } else {
                turnOffLED();
              }
              // buzzer activation
              /* 
              changeDutyCylce(5, true);
              */
          } else {
            // turn everything off
            turnOffLED();
            //changeDutyCycle(0, false);
          }
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