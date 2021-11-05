#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

uint16_t OutputCompare(uint16_t prescaler, uint8_t milliseconds){
	uint16_t freq_scaled = F_CPU/prescaler; //15625
	uint16_t seconds = milliseconds/1000;   //0,01
	uint16_t ticks = freq_scaled*seconds;   //156,25
	ticks = ticks - 1;						//Correct for starting at 0

	return ticks;
}

void timer_init() {
	//--- TIMER0 ---//
		/*Enable CTC*/
	/*
  	 Mode | WGM02 | WGM01 | WGM00 | Timer/Counter Mode of Operation | TOP | Update of OCR0x at| TOV Flag Set on|
	------|----------------------------------------------------------------------------------------------------  
    	0 |	  0 	  0 		0 				Normal	   			  0xFF       Immediate            MAX
    	1 |	  0 	  0 		1 				PWM, Phase Correct    0xFF          TOP              BOTTOM
		2 |	  0  	  1 		0 				CTC 				  OCRA 		 Immediate 			  MAX
    	3 |   0       1         1               Fast PWM              0xFF        BOTTOM              MAX
    	5 |   1       0         1               PWM, Phase Correct    OCRA          TOP              BOTTOM
    	7 |   1       1         1               Fast PWM              OCRA        BOTTOM              TOP	
	CTC = 0|1|0
	*/
	TCCR0A &= ~(1 << WGM00);
	TCCR0A |= (1 << WGM01);
	TCCR0A &= ~(1 << WGM02);

    /*Prescaler 1024*/
	/*
	CA02 CA01 CS00 Description
	  0    0    0  No clock source (Timer/Counter stopped).
	  0    0    1  clkI/O/1 (No prescaling)
	  0    1    0  clkI/O/8 (From prescaler)
	  0    1    1  clkI/O/64 (From prescaler)
	  1    0    0  clkI/O/256 (From prescaler)
	  1    0    1  clkI/O/1024 (From prescaler)
	  1    1    0  External clock source on T0 pin. Clock on falling edge.
	  1    1    1  External clock source on T0 pin. Clock on rising edge.
	  1024 = 1|0|1
	*/
	TCCR0B |= (1 << CS00) | (1 << CS02);
	TCCR0A &= ~(1 << CS01);
    
	/* Frequency based on prescaler 1024 and 10 milliseconds*/
	OCR0A = OutputCompare(1024, 10);
    
	/*Counter init 0*/
	TCNT0 = 0;

	/*TC0 Interrupt Mask Register */
	/*	
		Bit 2 – OCIEB: Timer/Counter0, Output Compare B Match Interrupt Enable
			When the OCIE0B bit is written to one, and the I-bit in the Status Register is set, 
			the Timer/Counter Compare Match B interrupt is enabled. The corresponding interrupt 
			is executed if a Compare Match in Timer/Counter occurs, i.e., when the OCF0B bit is set in TIFR0.
		Bit 1 – OCIEA: Timer/Counter0, Output Compare A Match Interrupt Enable
			When the OCIE0A bit is written to one, and the I-bit in the Status Register is set, 
			the Timer/Counter0 Compare Match A interrupt is enabled. The corresponding interrupt 
			is executed if a Compare Match in Timer/Counter0 occurs, i.e., when the OCF0A bit is set in TIFR0.
		Bit 0 – TOIE: Timer/Counter0, Overflow Interrupt Enable

		Output Compare A Match Interrupt Enable = OCIEA
	*/
	TIMSK0 |= (1<<OCIE0A);

	//--- Timer 2 ---//
    /*Fast PWM*/
	/*
	Mode | WGM22 | WGM21 | WGM20 | Timer/Counter Mode of Operation | TOP | Update of OCR0x at | TOV Flag Set on(1)
	0 	 |   0   |   0   |   0   | Normal                          | 0xFF|   Immediate        | MAX
	1 	 |   0   |   0   |   1   | PWM, Phase Correct              | 0xFF|   TOP              | BOTTOM 
	2    |   0   |   1   |   0   | CTC                             | OCRA|   Immediate        | MAX
	3    |   0   |   1   |   1   | Fast PWM                        | 0xFF|   BOTTOM           | MAX
	5    |   1   |   0   |   1   | PWM, Phase Correct              | OCRA|   TOP              | BOTTOM 
	7    |   1   |   1   |   1   | Fast PWM                        | OCRA|   BOTTOM           | TOP
	Fast PWM, TOP = 255 (0xFF) = 0|1|1
*/
	TCCR2A |= (1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B &= ~(1 <<  WGM22); 

	/*Non inverting Mode*/
	/*
	COM2A1 COM2A0 Description
	  0      0 	  Normal port operation, OC2A disconnected.
	  0      1	  WGM22 = 0: Normal Port Operation, OC2A Disconnected 
	 			  WGM22 = 1: Toggle OC2A on Compare Match	
	  1      0 	  Clear OC2A on Compare Match, set OC2A at BOTTOM (non-inverting mode)
	  1      1 	  Set OC2A on Compare Match, clear OC2A at BOTTOM (inverting mode)

	  Clear OC2A on Compare Match, set OC2A at BOTTOM (non-inverting mode) = 1|0
	  */
	TCCR2A &= ~(1 << COM2A0);
	TCCR2A |= (1 << COM2A1);
	
   
	/*
	CA22 | CA21 | CS20 | Description
	  0  |   0  |   0  | No clock source (Timer/Counter stopped).
      0  |      |   1  | clkI/O/1 (No prescaling)
      0  |   1  |   0  | clkI/O/8 (From prescaler)
      0  |   1  |   1  | clkI/O/32 (From prescaler)
      1  |   0  |   0  | clkI/O/64 (From prescaler)
      1  |   0  |   1  | clkI/O/128 (From prescaler)
      1  |   1  |   1  | clkI/O/1024 (From prescaler)
	 Prescaler 64 = 1|0|0
	*/
	TCCR2B &= ~(1 << CS20) | (1 << CS21);
	TCCR2B |= (1 << CS22);
}