/*
 * File Name : main.c
 * Purpose : Control fan speed
 * Creation Date : 01-05-2013
 * Last Modified : lör  4 maj 2013 21:02:58
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>

// We need to include interrupt to get interrupt support, duh
#include <avr/interrupt.h>

volatile uint8_t pwm = 0;
int main (void){
	// Disable interrupts while in setup phase
	cli();
	// Set as output
	DDRB |= (1 << PB0) | (1 << PB2);
	// Enable interrupt on "rising edge"
	PCMSK |= (1 << PIND2);
	MCUCR |= (1 << ISC01)|(1 << ISC00);
	// Enable interrupts
	GIMSK |= (1 << INT0);
	// Stop timer0
	TCCR0B = 0;
	// Select fast PWM mode
	TCCR0A = (1 << WGM00)|(1 << WGM01);
	// clear OC0A on Compare match, set when counting up
	TCCR0A |= (1 << COM0A1);
	// Start at 0
	OCR0A = 0x00;
	TCCR0B = (1 << CS00);
	sei();
	// Don't do any pwm, everything done in ISR
	for(;;) {
			PORTB ^= (1 << PB0);
			_delay_ms(100);
	}
	return 0;
}

ISR (INT0_vect) {
	if(pwm < 255)
		pwm = pwm + 15;
	else
		pwm = 0;
	OCR0A = pwm;
}

