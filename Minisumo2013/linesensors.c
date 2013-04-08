/*
 * File Name : linesensors.c
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
<<<<<<< HEAD
 * Last Modified : mån  8 apr 2013 18:51:43
=======
 * Last Modified : mån  8 apr 2013 18:51:43
>>>>>>> cf3adc64ff4cc44fcaba83dd79a920657e05af02
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "linesensors.h"

void init_linesensors() {
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


