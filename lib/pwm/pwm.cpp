// Author: Kris Rockowitz       
// Net ID: rockowitzks      
// Date: 10 March 2019   
// Assignment:     Lab 4
// Description: This file implements the PWM element.
//----------------------------------------------------------------------//



#include "pwm.h"
#include "timer.h"  
#include <avr/io.h>

const int C_FREQ = 261;
const int D_FREQ = 294;
const int E_FREQ = 329;
const int F_FREQ = 349;
const int G_FREQ = 391;
const int gS_FREQ = 415;
const int A_FREQ = 440;
const int aS_FREQ = 455;
const int B_FREQ = 466;
const int cH_FREQ = 523;
const int cSH_FREQ = 554;
const int dH_FREQ = 587;
const int dSH_FREQ = 622;
const int eH_FREQ = 659;
const int fH_FREQ = 698;
const int fSH_FREQ = 740;
const int gH_FREQ = 784;
const int gSH_FREQ = 830;
const int aH_FREQ = 880;

#define TIMER1_PRESCALER (uint8_t) 8
#define c (F_CPU / (C_FREQ * TIMER1_PRESCALER * 2) - 1)
#define d (F_CPU / (D_FREQ * TIMER1_PRESCALER * 2) - 1)
#define e (F_CPU / (E_FREQ * TIMER1_PRESCALER * 2) - 1)
#define f (F_CPU / (F_FREQ * TIMER1_PRESCALER * 2) - 1)
#define g (F_CPU / (G_FREQ * TIMER1_PRESCALER * 2) - 1)
#define gS (F_CPU / (gS_FREQ * TIMER1_PRESCALER * 2) - 1)
#define a (F_CPU / (A_FREQ * TIMER1_PRESCALER * 2) - 1)
#define aS (F_CPU / (aS_FREQ * TIMER1_PRESCALER * 2) - 1)
#define b (F_CPU / (B_FREQ * TIMER1_PRESCALER * 2) - 1)
#define cH (F_CPU / (cH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define cSH (F_CPU / (cSH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define dH (F_CPU / (dH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define dSH (F_CPU / (dSH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define eH (F_CPU / (eH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define fH (F_CPU / (fH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define fSH (F_CPU / (fSH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define gH (F_CPU / (gH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define gSH (F_CPU / (gSH_FREQ * TIMER1_PRESCALER * 2) - 1)
#define aH (F_CPU / (aH_FREQ * TIMER1_PRESCALER * 2) - 1)

void initPWMTimer3(){
// pin E3 for timer 3, OC3A
    DDRE |= (1 << DDE3);
// set the timer mode to fast PWM, non inverting
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32)|(1 << CS30);

    OCR3A = 0; //1024
}

void triggerAlarm(volatile bool* deviceOn){
// change the duty cycle
    // decide which motor needs to change, change the duty cycle
    while(*deviceOn){
        //Play first section
      firstSection(deviceOn);
    
      //Play second section
      secondSection(deviceOn);
    
      //Variant 1
      beep(f, 250, *deviceOn);  
      beep(gS, 500, *deviceOn);  
      beep(f, 350, *deviceOn);  
      beep(a, 125, *deviceOn);
      beep(cH, 500, *deviceOn);
      beep(a, 375, *deviceOn);  
      beep(cH, 125, *deviceOn);
      beep(eH, 650, *deviceOn);

      if (*deviceOn) {
        delayMs(500);
      }
      else {
        break;
      }
      //Repeat second section
      secondSection(deviceOn);
    
      //Variant 2 
      beep(f, 250, *deviceOn);  
      beep(gS, 500, *deviceOn);  
      beep(f, 375, *deviceOn);  
      beep(cH, 125, *deviceOn);
      beep(a, 500, *deviceOn);  
      beep(f, 375, *deviceOn);  
      beep(cH, 125, *deviceOn);
      beep(a, 650, *deviceOn);  

      if (*deviceOn)
        delayMs(650);
    }
    OCR3A = 0;
}

void beep(int note, unsigned int duration, volatile bool on)
{
  //Play tone on buzzerPin
  if (!on) 
    return;

  DDRE |= (1 << DDE3);
  OCR3A = note;
  delayMs(duration);
 
  //Stop tone on buzzerPin
  DDRE &= ~(1 << DDE3);
  delayMs(50);
}

void firstSection(volatile bool *deviceOn)
{
  beep(a, 500, *deviceOn);
  beep(a, 500, *deviceOn);    
  beep(a, 500, *deviceOn);
  beep(f, 350, *deviceOn);
  beep(cH, 150, *deviceOn);  
  beep(a, 500, *deviceOn);
  beep(f, 350, *deviceOn);
  beep(cH, 150, *deviceOn);
  beep(a, 650, *deviceOn);
 
  if (*deviceOn)
    delayMs(500);
  else 
    return;

  beep(eH, 500, *deviceOn);
  beep(eH, 500, *deviceOn);
  beep(eH, 500, *deviceOn);  
  beep(fH, 350, *deviceOn);
  beep(cH, 150, *deviceOn);
  beep(gS, 500, *deviceOn);
  beep(f, 350, *deviceOn);
  beep(cH, 150, *deviceOn);
  beep(a, 650, *deviceOn);
 
  if (*deviceOn) {
    delayMs(500);
  }
}
 
void secondSection(volatile bool *deviceOn)
{
  beep(aH, 500, *deviceOn);
  beep(a, 300, *deviceOn);
  beep(a, 150, *deviceOn);
  beep(aH, 500, *deviceOn);
  beep(gSH, 325, *deviceOn);
  beep(gH, 175, *deviceOn);
  beep(fSH, 125, *deviceOn);
  beep(fH, 125, *deviceOn);    
  beep(fSH, 250, *deviceOn);
  
  if (*deviceOn) {
    delayMs(325);
  }
  else 
    return;

  beep(aS, 250, *deviceOn);
  beep(dSH, 500, *deviceOn);
  beep(dH, 325, *deviceOn);  
  beep(cSH, 175, *deviceOn);  
  beep(cH, 125, *deviceOn);  
  beep(b, 125, *deviceOn);  
  beep(cH, 250, *deviceOn);  
  
  if (*deviceOn)
    delayMs(350);
}