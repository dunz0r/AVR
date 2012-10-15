/*
 * File Name : timers.c
 * Purpose : Timer inits and functions
 * Creation Date : 23-09-2012
 * Last Modified : mån 15 okt 2012 02:09:57
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "timers.h"
/*{{{ Initliaze TIMER1*/
void init_timer1(void)
{
	/* Set initial timer value */
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 |= (1 << TOIE1); /* Enable timer overflow interrupt */
	TCCR1B |= (1 << CS12); /* Prescaler at 1024 */
}
/*}}}*/
