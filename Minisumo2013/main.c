/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : Thu 17 Jan 2013 18:31:27 CET
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// USART
#include "usart.h"
// ADC with interrupts
#include "adc.h"


// Various utils
#include "utils.h"
#include "macros.h"

#define LED 5,B

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

int main(void) {
	init_adc();
	init_usart();
	init_motors();
	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Enable interrupts
	sei();
	set_output(LED);
	output_high(LED);

	for(;;) {
		printf("0: %i\t 1: %i\n", ad_value[0], ad_value[1]);
		set_motors(255,255);
		_delay_ms(500);
	}
}
