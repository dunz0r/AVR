/*
 * File Name : sidesensors.c
 * Purpose : Read the digital sharps at the sides of the robot
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 16:50:19
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "sidesensors.h"

void init_sidesensors(void) {
	// Set as inputs
	DDRB &= ~(1 << DDB4);
	DDRB &= ~(1 << DDB5);
}
