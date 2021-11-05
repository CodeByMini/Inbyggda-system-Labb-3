#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "button.h"
#include "timer.h"

volatile int buttonState = 0;

ISR(TIMER0_COMPA_vect) {
	button_state(&buttonState);
}

int main (void) {
	uart_init();
	timer_init();
	/* Enable Global Interrupt */
	sei(); 

	/* Keep track if the button has been pressed or not */
	int lastButtonState = 0; 

	while (1) {
		/* If the button is pressed but yet to be released */
		if (buttonState == 1 && lastButtonState == 0){
			printf_P(PSTR("pressed\r\n"));
			lastButtonState = buttonState;
		}
		/* if the button has been released and last it was pushed*/
		if (buttonState == 0 && lastButtonState == 1){
			printf_P(PSTR("released\r\n"));
			lastButtonState = buttonState;
		}
	}
	return 1;
}
