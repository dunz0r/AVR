/*
 * File Name : startpin.c
 * Purpose :
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 01:25:30
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "startpin.h"

/*{{{ Setup ISR etc */
void init_startpin(void) {

	// Enable Pin Change Interuppt 1
	PCICR |= (1 << PCIE1);
	// Enable trigger on PCINT1(PB1)
	PCMSK0 |= (1 << PCINT1);
	sei();
}
/*}}}*/

ISR(PCINT1_vect) {
	if(PORTB & (1 << PB1))
	set_heading(200,200);	
	else
	set_motors(0,0);
}

