/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 05:36:44
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

/*
 * Defines for pins
 *
 */
#define LED 5,B

/*
 * Function prototypes
 *
 */
void delay_ms(uint16_t ms);

/*
 * Main function
 *
 */
int main (void)
{
	unsigned char elapsed_seconds = 0; /* Make a new counter variable and initialize to zero */
	set_output(LED);
	TCCR1B |= (1 << CS10) | (1 << CS11); /* Set up timer */
	while(1)
	{
		/* True when matching ~1 second */
		if ( TCNT1 >= 15624 )
		{
			TCNT1 = 0; /* Reset timer */
			elapsed_seconds++;
			if ( elapsed_seconds == 60 )
			{
				elapsed_seconds = 0;
				toggle_output(LED); /* Flip bit(toggle) LED */
			}
		}
	}
}

/*
 * For longer delays
 *
 */
void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

