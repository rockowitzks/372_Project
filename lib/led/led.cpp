#include "led.h"

void initLED(){
    //using A1 as out put to led
    DDRA |= (1<<DDA1);
    
}