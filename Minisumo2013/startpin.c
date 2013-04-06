/*
 * File Name : startpin.c
 * Purpose : Startmodule, http://startmodule.com
 * Creation Date : 26-02-2013
 * Last Modified : lör  6 apr 2013 20:35:29
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
}
/*}}}*/
