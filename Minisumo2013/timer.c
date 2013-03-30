/*
 * File Name : timer.c
 * Purpose : Timer1
 * Creation Date : 2013-01-16
 * Last Modified : lör 30 mar 2013 13:19:47
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "timer.h"

void init_timer1(void) {
	// Mode 4, CTC on OCR1A
	TCCR1B |= (1 << WGM12);
	
	// 62500
	OCR1A = 0xF424;
}

void start_timer1(void) {
	// Start the timer
	TCCR1B |= (1<<CS10);
	
	//Set interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);

	// Set prescaler to 1024, start timer
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);
}

void stop_timer1(void) {
	// Stop the timer
	TCCR1B &= ~(1<<CS10);

	// Clear prescaler to 1024
	TCCR1B &= ~(1 << CS12);
	TCCR1B &= ~(1 << CS10);
	// Clear interrupt on compare match
	TIMSK1 &= ~(1 << OCIE1A);
}

// When the timer triggers, make J-turn
ISR (TIMER1_COMPA_vect)
{

	binary_led(2);
	set_heading(-(FULL_SPEED), 255);
	_delay_ms(STATE_DELAY);
	set_heading(-(FULL_SPEED), 0);
	_delay_ms(STATE_2);
	set_heading(-(FULL_SPEED), -255);
	_delay_ms(STATE_DELAY);
}
