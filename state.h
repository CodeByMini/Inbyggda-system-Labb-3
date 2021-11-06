#ifndef STATE_H
#define STATE_H

#include <stdio.h>

#define NUMBER_OF_STATES 4

typedef struct{
    int state;
    int pwm;
    int dir;
    unsigned long last;
}STATE;

void change_state(STATE*);
void handle_state(STATE*);

#endif