/*
 * File Name : startpin.c
 * Purpose :
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 11:32:48
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "startpin.h"

/*{{{ Setup ISR etc */
void init_startpin(void) {

	// Set as output
	DDRB &= ~(1 << DDB1);
	// Enable Pin Change Interuppt 1
	PCICR |= (1 << PCIE0);
	// Enable trigger on PCINT1(PB1)
	PCMSK0 |= (1 << PCINT1);
	sei();
}
/*}}}*/

ISR(PCINT1_vect) {
	if(!(PINB & (1 << PB1))){
		set_motors(200,200);
		_delay_ms(500);
	}
}

