#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "led.h"
#include "timer.h"
#include "serial.h"
#include "state.h"
#include "button.h"

#define DELAY 1

int main (void) {
	uart_init();
	button_init();
	adc_init();
	timer_init();
	LED_init();

	/* 
		Enable Global Interrupts
	*/
	sei(); 
	
	printf_P(PSTR("Hello World\r\n"));

	/* Set up starting state
		int state 			= 0 Start at default case
    	int pwm   			= 1 Initial value for pwm, used in simple_ramp() and switcher()
		int dir   			= 1 Initial value for direction, used in simple_ramp()
		unsigned long last 	= 0 used for delaying simple_ramp() and switcher()
	*/
	volatile STATE state = {0,1,1,0};
	
	while (1) {
		change_state(&state);
		handle_state(&state);
	}
	return 1;
}
