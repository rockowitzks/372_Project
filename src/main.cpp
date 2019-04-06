#include <Arduino.h>
#include "led.h"
#include "pir.h"

int main(void){
  initPIR();
  initLED();
  while(1){
    if(PINA & (1<<PINA0)){
      PORTA |= (1<<PORTA0);
    }
    else{
      PORTA &= ~(1<<PORTA0);
    }
  }
  
}