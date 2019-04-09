// PB1 Switch
#include "switch.h"


void initSwitchPB1(){
  DDRB &= ~(1 << DDB1); // Initializes pull-up resistor on PB1 and sets it into input mode
  PORTB |= (1 << PORTB1); // enable pull-up for PORTB1

  PCICR |= (1 << PCIE0);      // enable PCINT for 7-0
  PCMSK0 |= (1 << PCINT1);    // enable PCINT for PCINT1
}