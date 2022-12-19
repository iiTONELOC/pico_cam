#ifndef ECHO_LOCATION_H
#define ECHO_LOCATION_H
#include "pico/stdlib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Echo location sensor pins
extern uint ECHO_PIN;
extern uint TRIG_PIN;

// Echo location sensor variables
extern float echo_distance;

unsigned long pulseIn(uint pin, uint state);
float check_distance(void);
void init_echo_location(void);

#endif
