#include <avr/io.h>

#include "adc.h"
#include "led.h"
#include "timer.h"
#include "state.h"
#include "button.h"

/* if a debounce has occured update state to next state */
void change_state(STATE * state){
    if(debounce_button()){
        if(state->state>NUMBER_OF_STATES-1){
        state->state = 0;
    }
    state->state++;
    }
}

/*Using the state parameter inside STATE struct move program forward through functionality*/
void handle_state(STATE * state){
	/* Get a timer value to use in delaying simple_ramp() and switcher()*/
	unsigned long now = get_centis();

	switch(state->state){
	case 1:
		if(now - state->last > 0){
			/*Set PWM to new value*/
			OCR2A = simple_ramp(state);
			state->last = now;
		}
		break;
	case 2:
		/* Get value from potentiometer reading*/
		OCR2A = getadc_value();
		break;
	case 3:
		if(now - state->last > 50){
			/*Set PWM to new value*/
			OCR2A = switcher(state);
			state->last = now;
		}
		break;
	default:
		/*Blackout*/
		OCR2A = 255;
		break;
	}
}