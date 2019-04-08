// Description: Function prototypes for pwm.h
//----------------------------------------------------------------------//

#ifndef PWM_H
#define PWM_H

void initPWMTimer3();
void triggerAlarm(volatile bool *deviceOn);
void firstSection();
void secondSection();
void beep(int note, unsigned int duration);

#endif