/*
 * File Name : main.c
 * Purpose : Blink an LED
 * Creation Date : 01-05-2013
 * Last Modified : tor 19 jun 2014 00:53:11
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>

int main (void){
	// Set as output
	DDRD |= (1 << PD5);
	int i = 0;
	for(;;) {
		PORTD |= (1 << PD5);
		_delay_ms(200);
		PORTD &= ~(1 << PD5);
		_delay_ms(200);
	}
}
