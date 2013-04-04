/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
<<<<<<< HEAD
 * Last Modified : tor  4 apr 2013 18:07:11
=======
 * Last Modified : tor  4 apr 2013 18:07:11
>>>>>>> cf3adc64ff4cc44fcaba83dd79a920657e05af02
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "linesensors.h"

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

	} else {
		/* {{{ INT0 */
		// Set PD2 to be an input
		DDRD &= ~(1 << PD2);
		// Trigger on low
		// TODO test with any logic change
		EICRA |= (1 << ISC01);
		EICRA |= (1 << ISC00);
		// Enable INT0
		EIMSK |= (1 << INT0);
		/* }}} */

		/* {{{ INT1 */
		// Set PD3 to be an input
		DDRD &= ~(1 << PD3);

		// Trigger on low
		// TODO test with any logic change
		EICRA |= (1 << ISC10);
		EICRA |= (1 << ISC11);
		// Enable INT1
		EIMSK |= (1 << INT1);
		/* }}} */

	}
}

ISR (INT0_vect) {
	// "Smoothing"
	_delay_ms(1);
	if(ON_BLACK) {
		if(!(PIND & (1 << PD2))){
			binary_led(1);
			set_motors(-(FULL_SPEED),-(FULL_SPEED));
			_delay_ms(STATE_2);
			set_heading(0,200);
			_delay_ms(STATE_DELAY);
		}
	} else {
		if(PIND & (1 << PD2)){
			binary_led(1);
			set_motors(-(FULL_SPEED),-(FULL_SPEED));
			_delay_ms(STATE_3);
			set_heading(0,200);
			_delay_ms(STATE_DELAY);
		}
	}
}

ISR (INT1_vect) {
	// "Smoothing"
	_delay_ms(1);
	if(ON_BLACK){
		if(!(PIND & (1 << PD3))){
			binary_led(4);
			set_motors(-(FULL_SPEED),-(FULL_SPEED));
			_delay_ms(STATE_3);
			set_heading(0,-200);
			_delay_ms(STATE_DELAY);
		}
	} else {
		if(PIND & (1 << PD3)){
			binary_led(4);
			set_motors(-(FULL_SPEED),-(FULL_SPEED));
			_delay_ms(STATE_3);
			set_heading(0,-200);
			_delay_ms(STATE_DELAY);
		}
	}
}
