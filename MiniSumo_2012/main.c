/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 08:20:04
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

/*
 * Defines for pins
 *
 */
#define LED 5,B

/*
 * Main function
 *
 */
int main (void)
{
	set_output(LED);
	/*
	TCCR1B |= ( 1 << WGM12); * Configure timer 1 for CTC mode *
	TIMSK1 |= (1 << OCIE1A); * Enable CTC interrupt *
	OCR1A = 1562; * Set CTC compare to 1/16 *
	sei(); * Enable global interrupts *
	TCCR1B |= ((1 << CS10 ) | (1 << CS11)); * Start timer at Fcpu/64 *
	*/
	while(1)
	{
		toggle_output(LED);
		_delay_ms(255);
		_delay_ms(255);
	}
}
/*
 * Interrupts
 *
 */

ISR(TIMER1_COMPA_vect)
{
	toggle_output(LED); /* Flip bit(toggle) LED */
}
