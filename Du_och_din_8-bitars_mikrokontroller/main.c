/*
 * File Name : main.c
 * Purpose : Blink an LED
 * Creation Date : 01-05-2013
 * Last Modified : ons  1 maj 2013 22:53:20
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>

int main (void){
	// Set as output
	DDRB |= (1 << PB0) | (1 << PB2) | (1 << PB3) | (1 << PB4);
	int i = 0;
	for(;;) {
		i++;
		if(i > 3)
			i=0;
		PORTB |= (1 << i);
		_delay_ms(100);
		PORTB &= ~(1 << i);
	}
}
