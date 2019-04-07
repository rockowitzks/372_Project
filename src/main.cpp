
#include <Arduino.h>
#include "led.h"
#include "pir.h"
#include "timer.h"


int main(void){
  Serial.begin(9600);
  initLED();
  initPIR();
  initTimer1();
  while(1){
    //testing PIR detector
    bool motion = detectMotion();
    //Serial.println(motion);
    if(motion){
      lightLED();
    }
    else{
      turnOffLED();
    }
    delayMs(500);
  }
  
}