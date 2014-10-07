/*
 * File Name : switch.c
 * Purpose : Read a switch
 * Creation Date : 18-03-2013
 * Last Modified : sön  7 sep 2014 20:36:55
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "switch.h"
void init_switch(void) {
	// Set PB2 as input
	DDRB &= ~(1 << PB2);
}

uint8_t switch_is_pressed(void) {
	uint8_t switch_pressed = PINB & (1 << PB2);
	return switch_pressed;
}
