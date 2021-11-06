#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile int counter = 0;
volatile unsigned long centis = 0;

ISR(TIMER0_COMPA_vect) {
	ADCSRA |= (1 << ADSC);
	counter++;
	centis++;
}

unsigned long get_centis(){
	return centis;
}

int get_counter(){
	return counter;
}

void set_counter(int newCounter){
	counter = newCounter;
}


uint16_t OutputCompare(uint16_t prescaler, uint8_t milliseconds){
	uint16_t freq_scaled = F_CPU/prescaler; //15625
	uint16_t seconds = milliseconds/1000;   //0,01
	uint16_t ticks = freq_scaled*seconds;   //156,25
	ticks = ticks - 1;						//Correct for starting at 0 = 155

	return ticks;
}

void timer_init() {

	 //TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
	 //TCCR0B |= (1 << CS00) | (1 << CS01);

	// TCCR2A |= (1 << WGM21);

	// TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);

	// TIMSK2 |= (1 << OCIE2A); //enabling output compare a match interrupt

	// OCR2A = 155;
	// TCNT2 = 0;
	
	//TIMER2 PWM
    /*Fast PWM*/
	TCCR2A |= (1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B &= ~(1 <<  WGM22); 

	/*Non inverting Mode*/
	TCCR2A &= ~(1 << COM2A0);
	TCCR2A |= (1 << COM2A1);
	
    /*Prescaler 64*/
	TCCR2B &= ~(1 << CS20) | (1 << CS21);
	TCCR2B |= (1 << CS22);

	//TIMER0
	/*Enable CTC*/
	TCCR0A &= ~(1 << WGM00);
	TCCR0A |= (1 << WGM01);
	TCCR0A &= ~(1 << WGM02);

    /*prescaler 1024*/
	TCCR0B |= (1 << CS00) | (1 << CS02);
	TCCR0A &= ~(1 << CS01);
    
	/* Frequency based on prescaler 1024 and 10 milliseconds*/
	OCR0A = OutputCompare(1024, 10);
    
	/*Counter init 0*/
	TCNT0 = 0;

	TIMSK0 |= (1<<OCIE0A);
}