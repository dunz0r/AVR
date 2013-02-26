/*
 * File Name : startpin.c
 * Purpose : Startmodule, http://startmodule.com
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 16:21:14
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "startpin.h"

/*{{{ Setup ISR etc */
void init_startpin(void) {

	// Set as input
	DDRB &= ~(1 << DDB1);
	// Enable Pin Change Interuppt 0
	PCICR |= (1 << PCIE0);
	// Enable trigger on PCINT1(PB1)
	PCMSK0 |= (1 << PCINT1);
	sei();
}
/*}}}*/

ISR(PCINT0_vect) {
	binary_led(7);
	_delay_ms(100);
	binary_led(6);
	_delay_ms(100);
	binary_led(0);
	set_motors(0,0);
}

