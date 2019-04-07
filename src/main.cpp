
#include <Arduino.h>
#include "led.h"
#include "pir.h"
#include "timer.h"
#include "pwm.h"

/*
int main(void){
  //Serial.begin(9600);
  initLED();
  // Serial.println("began initializing PIR");
  // Serial.flush();
  initPIR();
  initPWMTimer3();
  // int i =0;
  // while(i < 6)
  //   delayMs(1000);
  //  Serial.println("finished initializing PIR");
  // Serial.flush();
  initTimer1();
  while(1){
    changeDutyCycle(1023, true);
    //testing PIR detector

    // bool motion = detectMotion();
    // Serial.println(motion);
    // if(motion){
    //   lightLED();
    // }
    // else{
    //   turnOffLED();
    // }
    // delayMs(500);
  }
  
}

*/

const uint16_t A4_FREQ = 440;
const uint16_t C5_FREQ = 523;
const uint16_t D6_FREQ = 1175;

// OCR1A values

#define A4 (F_CPU / (A4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define C5 (F_CPU / (C5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D6 (F_CPU / (D6_FREQ * TIMER1_PRESCALER * 2) - 1)

//new song

int main(void)
{
   // Set OC1A as output pin
    initTimer1();
    initPWMTimer3();
    
    triggerAlarm(true);

    while (1)
    {
     
    }
}

