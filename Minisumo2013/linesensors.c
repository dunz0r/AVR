/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : ons  6 feb 2013 14:56:21
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "linesensors.h"
void init_linesensors(void) {
	/* {{{ INT0 */
	// Set PD2 to be an input
	DDRD &= ~(1 << DDD2);

	// Trigger on falling edge
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	/* }}} */

	/* {{{ INT1 */
	// Set PD2 to be an input
	DDRD &= ~(1 << DD3);

	// Trigger on falling edge
	EICRA |= (1 << ISC11);
	EIMSK |= (1 << INT1);
	/* }}} */
}

ISR (INT0_vect) {
	set_heading(0,255);
	printf("int 0 triggered\n");
}

ISR (INT1_vect) {
	set_heading(255,0);
	printf("int 1 triggered\n");
}
