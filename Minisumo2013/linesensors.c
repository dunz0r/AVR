/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : lör 23 mar 2013 11:03:47
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "constants.h"
#include "linesensors.h"
void init_linesensors() {
	/* {{{ INT0 */
	if(ON_BLACK){
		// Set PD2 to be an input
		DDRD &= ~(1 << PD2);
		// Trigger on falling edge
		// TODO test with any logic change
		EICRA |= (1 << ISC01);
		// Enable INT0
		EIMSK |= (1 << INT0);
	} else {
		// Set PD2 to be an input
		DDRD &= ~(1 << PD2);

		// Trigger on rising edge
		// TODO test with any logic change
		EICRA &= ~(1 << ISC01);
		EICRA &= ~(1 << ISC00);
		// Enable INT0
		EIMSK |= (1 << INT0);
	}

	/* }}} */
	/* {{{ INT1 */
	if(ON_BLACK){
		// Set PD3 to be an input
		DDRD &= ~(1 << PD3);

		// Trigger on falling edge
		// TODO test with any logic change
		EICRA |= (1 << ISC11);
		// Enable INT1
		EIMSK |= (1 << INT1);
	} else {
		// Set PD3 to be an input
		DDRD &= ~(1 << PD3);

		// Trigger on rising edge
		// TODO test with any logic change
		EICRA &= ~(1 << ISC11);
		EICRA &= ~(1 << ISC10);
		// Enable INT1
		EIMSK |= (1 << INT1);
	}
	/* }}} */
}

ISR (INT0_vect) {
	_delay_ms(1);
	if(!(PIND & (1 << PD2))){
		set_heading(-255,0);
		_delay_ms(STATE_DELAY);
		set_heading(0,100);
		_delay_ms(STATE_DELAY);
	}
}

ISR (INT1_vect) {
	_delay_ms(1);
	if(!(PIND & (1 << PD3))){
		set_heading(-255,0);
		_delay_ms(STATE_DELAY);
		set_heading(0,-100);
		_delay_ms(STATE_DELAY);
	}
}
