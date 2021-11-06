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
	sei(); //enable interrupts
	printf_P(PSTR("Hello World\r\n"));

	volatile STATE state = {0,1,1};
	
	while (1) {
		change_state(&state);
		handle_state(&state);
	}
	return 1;
}
