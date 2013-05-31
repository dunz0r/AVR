/*
 * File Name : main.c
 * Purpose : Toggle LEDs
 * Creation Date : 01-05-2013
 * Last Modified : lör  4 maj 2013 21:14:56
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>

// We need to include interrupt to get interrupt support, duh
#include <avr/interrupt.h>

int main (void){
	// Disable interrupts while in setup phase
	cli();
	// Set as output
	DDRB |= (1 << PB0) | (1 << PB2);
	// Pins are input by default, no need to set DDRD
	// Enable interrupt on "rising edge"
	PCMSK |= (1 << PIND2);
	MCUCR |= (1 << ISC01)|(1 << ISC00);
	// Enable interrupts
	GIMSK |= (1 << INT0);
	sei();
	// Don't do anything, everything done in ISR
	for(;;) {
		PORTB ^= (1 << PB0);
		_delay_ms(300);
	}
	return 0;
}

ISR (INT0_vect) {
	PORTB ^= (1 << PB2);
}

