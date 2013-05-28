/*
 * File Name : leds.c
 * Purpose :
 * Creation Date : 26-02-2013
 * Last Modified : ons 24 apr 2013 20:40:34
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "leds.h"

void init_leds(void) {
	//DDRC |= (1 << 5);
	DDRC |= (1 << 4);
	DDRC |= (1 << 3);
}

void binary_led(uint8_t number) {
	switch(number) {
		case 0:
	//		PORTC &= ~(1 << 5);
			PORTC &= ~(1 << 4);
			PORTC &= ~(1 << 3);
			break;
		case 1:
	//		PORTC &= ~(1 << 5);
			PORTC &= ~(1 << 4);
			PORTC |= (1 << 3);
			break;
		case 2:
	//		PORTC &= ~(1 << 5);
			PORTC |= (1 << 4);
			PORTC &= ~(1 << 3);
			break;
		case 3:
	//		PORTC &= ~(1 << 5);
			PORTC |= (1 << 4);
			PORTC |= (1 << 3);
			break;
		case 4:
	//		PORTC |= (1 << 5);
			PORTC &= ~(1 << 4);
			PORTC &= ~(1 << 3);
			break;
		case 5:
	//		PORTC |= (1 << 5);
			PORTC &= ~(1 << 4);
			PORTC |= (1 << 3);
			break;
		case 6:
	//		PORTC |= (1 << 5);
			PORTC |= (1 << 4);
			PORTC &= ~(1 << 3);
			break;
		case 7:
	//		PORTC |= (1 << 5);
			PORTC |= (1 << 4);
			PORTC |= (1 << 3);
			break;
	}
}
