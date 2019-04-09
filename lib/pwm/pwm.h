// Description: Function prototypes for pwm.h
//----------------------------------------------------------------------//

#ifndef PWM_H
#define PWM_H

void initPWMTimer3();
void triggerAlarm(volatile bool* deviceOn);
void firstSection(volatile bool *deviceOn);
void secondSection(volatile bool *deviceOn);
void beep(int note, unsigned int duration, volatile bool on);

#endif