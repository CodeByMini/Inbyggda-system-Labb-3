#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "button.h"
#include "serial.h"
#include "timer.h"

#define DEBOUNCE 10

volatile int buttonState = 0;
volatile unsigned long lastInterrupt = 0;
volatile int isInterrupted = 0;

ISR(INT0_vect) {
  if(!isInterrupted){
	  lastInterrupt = get_centis();
	  isInterrupted = 1;
  }
}

int debounce_button(){
  if (isInterrupted) {
    if (get_centis() - lastInterrupt > DEBOUNCE) {
      isInterrupted = 0;
      return 1;
    }
  }
    return 0;
}

void button_init(){
    DDRD &= ~(1<<PD2);
    EICRA |= (1<<ISC01);
    EICRA &= ~(1<<ISC00);
    EIMSK |= (1<<INT0);
}