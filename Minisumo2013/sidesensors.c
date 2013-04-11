/*
 * File Name : sidesensors.c
 * Purpose : Read the digital sharps at the sides of the robot
 * Creation Date : 26-02-2013
 * Last Modified : tor 11 apr 2013 04:30:19
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
		return 1;
	else
		return 0;
}

uint8_t right_sensor_triggered(void) {
	if(!(PINB & (1 << PB5)))
		return 1;
	else
		return 0;
}
