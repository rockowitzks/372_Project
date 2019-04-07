#include "led.h"

void initLED(){
    //using A1 as out put to led
    DDRA |= (1 << DDA1);
    
}

void lightLED(){
    PORTA |= (1 << PORTA1);
}

void turnOffLED(){
    PORTA &= ~(1 << PORTA1);
}