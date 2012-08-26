/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 06:17:16
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <avr/io.h>
#include "macros.h"
#include "delay_ms.h"

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
	 /* TODO Enable CTC interrupt */
	 /* TODO Enable global interrupts */
	TCCR1B |= ( 1 << WGM12); /* Configure timer 1 for CTC mode */
	OCR1A = 15624; /* Set CTC compare value to 1Hz at 1MHz AVR clock with a prescaler of 64 */

	TCCR1B |= ((1 << CS10 ) | (1 << CS11)); /* Start timer at Fcpu/64 */
	while(1)
	{
		if (TIFR1 & (1 << OCF1A))
		{
			toggle_output(LED); /* Flip bit(toggle) LED */

			TIFR1 = (1 << OCF1A); /* Clear the CTC flag by writing a logic 1 to the set flag */
		}
	}
}
