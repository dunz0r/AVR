/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
<<<<<<< HEAD
 * Last Modified : ons 20 feb 2013 17:43:43
=======
 * Last Modified : ons 20 feb 2013 17:43:43
>>>>>>> 7bba52c3ef81a39893ce5df0da030eaa58a8f217
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "linesensors.h"
void init_linesensors(void) {
	/* {{{ INT0 */
	// Set PD2 to be an input
	DDRD &= ~(1 << PD2);
	// Trigger on falling edge
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	/* }}} */

	/* {{{ INT1 */
	// Set PD3 to be an input
	DDRD &= ~(1 << PD2);

	// Trigger on falling edge
	EICRA |= (1 << ISC11);
	EIMSK |= (1 << INT1);
	/* }}} */
}

ISR (INT0_vect) {
	_delay_ms(1);
	if(!(PIND & (1 << PD2))){
		set_heading(-255,0);
		_delay_ms(50);
		set_heading(0,95);
		_delay_ms(40);
		_delay_ms(200);
	}
}

ISR (INT1_vect) {
	_delay_ms(1);
	if(!(PIND & (1 << PD3))){
		set_heading(-255,0);
		_delay_ms(50);
		set_heading(0,-95);
		_delay_ms(100);
	}
}
