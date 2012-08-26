/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 17:06:21
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

volatile uint8_t count;

void init_timer1(void)
{
	/* Set initial timer value */
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 |= (1 << TOIE1); /* Enable timer overflow interrupt */
	TCCR1B |= (1 << CS12);
	sei();
}

/*
 * Main function
 *
 */
int main (void)
{
	set_output(LED);
	init_timer1();

	/* Infinite loop */
	for(;;);
}

ISR(TIMER1_OVF_vect)
{
	toggle_output(LED);
}
