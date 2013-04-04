/*
 * File Name : timer.c
 * Purpose : Timer1
 * Creation Date : 2013-01-16
 * Last Modified : tor  4 apr 2013 18:06:35
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "timer.h"

void init_timer1(void) {
	// Mode 4, CTC on OCR1A
	TCCR1B |= (1 << WGM12);
	
	// 65536
	OCR1A = 0xFFFF;
}

void start_timer1(void) {
	// Start the timer
	TCCR1B |= (1<<CS10);
	
	//Set interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);

	// Set prescaler to 1024, start timer
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

void stop_timer1(void) {
	// Stop the timer
	TCCR1B &= ~(1<<CS10);

	// Clear prescaler to 1024
	TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
	//TCCR1B &= ~(1 << CS10);
	TIMSK1 &= ~(1 << OCIE1A);
}


