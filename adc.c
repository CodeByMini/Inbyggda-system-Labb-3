#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

void adc_init() {
	/*
		| REFS1 | REFS0 | Voltage Reference Selection
		|   0   |   0   | AREF, Internal Vref turned off
        |   0   |   1   | AVCC with external capacitor at AREF pin
        |   1   |   1   | Internal 1.1V Voltage Reference with external capacitor at AREF pin
		ADC Left Adjust Result, REFS0: Reference Selection 01 
		= AVCC with external capacitor at AREF pin
	*/
	ADMUX |= (1 << ADLAR) | (1 << REFS0); 

	/* // ADC Prescaler Select 011 = 8 */
	/*
	ADPS2| ADPS1| ADPS0 | Division Factor
	0	 | 0    | 0     | 2
	0	 | 0    | 1     | 2
	0    | 1    | 0     | 4
	0    | 1    | 1     | 8
	1    | 0    | 0     | 16
	1    | 0    | 1     | 32
	1    | 1    | 0     | 64
	1    | 1    | 1     | 128
	Prescaler 8 = 0|1|1
*/
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);
	ADCSRA &= ~(1 <<ADPS2);

	/* // ADC Enable, ADC Interrupt Enable */
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
}