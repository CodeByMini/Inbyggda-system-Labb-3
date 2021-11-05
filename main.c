#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "led.h"
#include "timer.h"

int adcValue = 255;

ISR(TIMER0_COMPA_vect) {
	/* Start single conversion */
	ADCSRA |= (1 << ADSC);

	/* Set RED PWM value to potentiometer reading */
	OCR2A = adcValue;//flip_it_and_reverse_it(adcValue); //obsolete function due to unability to read 
}

ISR(ADC_vect) {
	/* Get value from ADC Data Register. Reading only the highest 8 bits out of 10*/
	adcValue = ADCH;
}

void main (void) {
	adc_init();
	timer_init();
	LED_init();
	sei(); //enable interrupts

	while (1) {}
}
