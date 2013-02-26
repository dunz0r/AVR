/*
 * File Name : startpin.c
 * Purpose :
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 01:04:44
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "startpin.h"

/*{{{ Setup ISR etc */
void init_startpin(void) {

	// Enable Pin Change Interuppt 0
	PCICR |= (1 << PCIE0);

	// Enable trigger on PCINT1(PB1)
	PCMSK0 |= (1 << PCINT1);
}
/*}}}*/

ISR(SIG_PIN_CHANGE0) {
	if(!(PIND & (1 << PB1))) {
		set_heading(-200,0);
		_delay_ms(1000);
}

