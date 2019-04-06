
#include <Arduino.h>
#include "led.h"
#include "pir.h"
#include "timer.h"


int main(void){
  Serial.begin(9600);
  initLED();
  Serial.println("began initializing PIR");
  Serial.flush();
  initPIR();
  // int i =0;
  // while(i < 6)
  //   delayMs(1000);
   Serial.println("finished initializing PIR");
  Serial.flush();
  initTimer1();
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
  
}