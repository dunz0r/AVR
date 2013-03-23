/*
 * File Name : startpin.c
 * Purpose : Startmodule, http://startmodule.com
 * Creation Date : 26-02-2013
 * Last Modified : lör 23 mar 2013 21:19:08
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

ISR(PCINT0_vect) {
	while(!(PINB & (1 << PB1))){
		set_motors(0,0);
		binary_led(1);
		_delay_ms(50);
		binary_led(4);
		_delay_ms(50);
		}
}
