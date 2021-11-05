#include <avr/io.h>
#include "button.h"

/* Set Digital pin 2 on Arduino to input ie: PD2*/
void button_init(){
    DDRD &= ~(1<<PD2);
}

/* Funtion to return a true value if a button press is detected*/
int button_pressed(){
    if(PIND & (1<<PIND2)){
		return 1;
	}
	return 0;
}

/* Change buttonstate based on button pushes*/
void button_state(int *buttonState){
    if(button_pressed()){
		*buttonState = 1;
	}
	else {
		*buttonState = 0;
	}
}