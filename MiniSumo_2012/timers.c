/*
 * File Name : timers.c
 * Purpose : Timer inits and functions
 * Creation Date : 23-09-2012
 * Last Modified : tis  1 jan 2013 21:33:39
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "timers.h"
/*{{{ Initialize TCNT0 for AD-conversions*/
void init_timer0(void)
{
	// Set initial timer value
	TCNT0=0;
	// Place TOP timer value to output compare register
	OCR0A=99;
	// Set CTC mode
	// and make toggle PD6/OC0A pin on compare match
	TCCR0A |=(1<<COM0A0)|(1<<WGM01);
}
/*}}}*/

/*{{{ Start Timer 0*//*}}}*/
void start_timer0(void)
{
	// Set prescaler to 8 and start timer
	TCCR0B |= (1<<CS01);
}
/*{{{ Initliaze TCCR1*/
void init_timer1(void)
{
	/* Set initial timer value */
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 |= (1 << TOIE1); /* Enable timer overflow interrupt */
	TCCR1B |= (1 << CS12); /* Prescaler at 1024 */
}
/*}}}*/
