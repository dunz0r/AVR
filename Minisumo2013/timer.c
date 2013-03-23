/*
 * File Name : timer.c
 * Purpose : Timer1
 * Creation Date : 2013-01-16
 * Last Modified : lör 23 mar 2013 18:52:35
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "timer.h"

void init_timer1(void) {

	// 62500
	OCR1A = 0xF4A1;

	// Mode 4, CTC on OCR1A
	TCCR1B |= (1 << WGM12);

}

void start_timer1(void) {
	// Start the timer
	TCCR1B |= (1<<CS10);

	// Set prescaler to 1024
	TCCR1B |= (1 << CS12);
	//Set interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);
}

void stop_timer1(void) {
	// Stop the timer
	TCCR1B &= ~(1<<CS10);

	// Set prescaler to 1024
	TCCR1B &= ~(1 << CS12);
	//Set interrupt on compare match
	TIMSK1 &= ~(1 << OCIE1A);
}

// When the timer triggers, make J-turn
ISR (TIMER1_COMPA_vect)
{
	binary_led(2);
	set_heading(-(FULL_SPEED), 255);
	_delay_ms(STATE_DELAY*4);
	set_heading(-(FULL_SPEED), 0);
	_delay_ms(STATE_DELAY*3);
}
