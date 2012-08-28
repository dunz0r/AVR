/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : mån 27 aug 2012 21:48:44
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"

/*
 * Defines for pins
 *
 */
#define LED 5,B
#define LED2 6,D

volatile uint8_t count;

void init_timer1(void)
{
	/* Set initial timer value */
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 |= (1 << TOIE1); /* Enable timer overflow interrupt */
	TCCR1B |= (1 << CS12); /* Prescaler at 1024 */
	sei();
}

/*
 * Main function
 *
 */
int main (void)
{
	set_output(LED2);
	/* set up PWM */
	OCR0A = 255;
	/* set non-inverting mode */
	TCCR0A |= (1 << COM0A1);
	/* set fast PWM Mode */
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	// set prescaler to 8 and starts PWM
	TCCR0B |= (1 << CS01);

	//set_output(LED);
	//init_timer1();

	/* Infinite loop */
	for(;;)
		for (int i = 255; i > 0; i--) {
			OCR0A= i;
			_delay_ms(5);
		}
}

ISR(TIMER1_OVF_vect)
{
	toggle_output(LED);
}
