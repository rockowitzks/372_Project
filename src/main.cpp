
#include <Arduino.h>
#include "adxl345.h"
#include "led.h"
#include "pir.h"
#include "timer.h"

#define thresh 300

int main(void){
  Serial.begin(9600);
  initLED(); //for testing
  initPIR(); //motion sensor
  initTimer1(); //for testing
  initADXL345(); //accelerometer
  while(1){
    //testing PIR detector
    //bool motion = detectMotion();
    int z = getZ();
    
    bool tooFar = (abs(z) > thresh);
    while(tooFar){ // took out motion here, but will need later
      lightLED();
      delayMs(100);
    }
    
    turnOffLED();
    
    delayMs(100);
  }
  return 0;
}