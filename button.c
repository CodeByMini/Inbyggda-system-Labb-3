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

/* Interrupt Service Routine for INT0 vector. ie: button connected to pin 2 on Arduino */
ISR(INT0_vect) {

  /* Start debounce check */
  if(!isInterrupted){
	  lastInterrupt = get_centis();
	  isInterrupted = 1;
  }
}

/* Debouncing buttons by only taking one push */ 
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
  /* Set pin2 as input */
    DDRD &= ~(1<<PD2);
    /* 
      ISC01 | ISC00 | Description
       0    |  0    | The low level of INT1 generates an interrupt request.
       0    |  1    | Any logical change on INT1 generates an interrupt request.
       1    |  0    | The falling edge of INT1 generates an interrupt request.
       1    |  1    | The rising edge of INT1 generates an interrupt request.
    */
    EICRA |= (1<<ISC01);
    EICRA &= ~(1<<ISC00);

    /*
       INT0: External Interrupt Request 0 Enable
    */
    EIMSK |= (1<<INT0);
}