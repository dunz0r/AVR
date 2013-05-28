/*
 * File Name : sidesensors.c
 * Purpose : Read the digital sharps at the sides of the robot
 * Creation Date : 26-02-2013
 * Last Modified : tis 23 apr 2013 22:21:00
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "sidesensors.h"

void init_sidesensors(void) {
	// Set as inputs
	DDRB &= ~(1 << DDB4);
	DDRB &= ~(1 << DDB5);
}

uint8_t left_sensor_triggered(void) {
	if(!(PINB & (1 << PB4)))
		return 0;
	else
		return 1;
}

uint8_t right_sensor_triggered(void) {
	if(!(PINB & (1 << PB5)))
		return 0;
	else
		return 1;
}
