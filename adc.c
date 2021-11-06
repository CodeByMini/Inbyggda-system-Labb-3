#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

volatile int adcValue = 255;

ISR(ADC_vect) {
	adcValue = ADCH;
}

void adc_init() {
	ADMUX |= (1 << ADLAR) | (1 << REFS0); //ADC Left Adjust Result, REFS0: Reference Selection 01 = AVCC with external capacitor at AREF pin

	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);	// ADC Prescaler Select 011 = 8
	ADCSRA |= (1 << ADEN) | (1 << ADIE); 	// ADC Enable, ADC Interrupt Enable
    sei();
}

int getadc_value(){
	return adcValue;
}