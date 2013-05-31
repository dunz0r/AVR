/*
 * File Name : main.c
 * Purpose : Blink an LED
 * Creation Date : 01-05-2013
 * Last Modified : tor  2 maj 2013 12:30:04
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>

int main (void){
	// Set as output
	DDRB |= (1 << PB0);
	int i = 0;
	for(;;) {
		PORTB |= (1 << PB0);
		_delay_ms(200);
		PORTB &= ~(1 << PB0);
		_delay_ms(200);
	}
}
