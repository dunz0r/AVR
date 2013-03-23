/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : lör 23 mar 2013 13:57:31
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "constants.h"
#include "linesensors.h"
#include "leds.h"

void init_linesensors() {
	if(ON_BLACK) {
		/* {{{ INT0 */
		// Set PD2 to be an input
		DDRD &= ~(1 << PD2);
		// Trigger on low
		// TODO test with any logic change
		EICRA &= ~(1 << ISC01);
		EICRA &= ~(1 << ISC00);
		// Enable INT0
		EIMSK |= (1 << INT0);
		/* }}} */

		/* {{{ INT1 */
		// Set PD3 to be an input
		DDRD &= ~(1 << PD3);

		// Trigger on low
		// TODO test with any logic change
		EICRA &= ~(1 << ISC10);
		EICRA &= ~(1 << ISC11);
		// Enable INT1
		EIMSK |= (1 << INT1);
		/* }}} */

	}
}

ISR (INT0_vect) {
	// "Smoothing"
	_delay_ms(1);
	if(!(PIND & (1 << PD2))){
		binary_led(1);
		set_heading(-255,0);
		_delay_ms(STATE_DELAY);
		set_heading(0,100);
		_delay_ms(STATE_DELAY);
	}
}

ISR (INT1_vect) {
	// "Smoothing"
	_delay_ms(1);
	if(!(PIND & (1 << PD3))){
		binary_led(4);
		set_heading(-255,0);
		_delay_ms(STATE_DELAY);
		set_heading(0,-100);
		_delay_ms(STATE_DELAY);
	}
}
