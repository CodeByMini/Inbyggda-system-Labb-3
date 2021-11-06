#include <avr/io.h>

#include "adc.h"
#include "led.h"
#include "timer.h"
#include "state.h"
#include "button.h"

void change_state(STATE * state){
    if(debounce_button()){
        if(state->state>NUMBER_OF_STATES-1){
        state->state = 0;
    }
    state->state++;
    }
}

void handle_state(STATE * state){
	int now = get_centis();
	switch(state->state){
	case 1:
		if(now - state->last > 1){
			OCR2A = simple_ramp(state);
			state->last = now;
		}
		break;
	case 2:
		OCR2A = getadc_value();
		break;
	case 3:
		if(now - state->last > 100){
			OCR2A = switcher(state);
			state->last = now;
		}
		break;
	default:
		OCR2A = 255;
		break;
	}
}