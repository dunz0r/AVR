/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : Mon 11 Feb 2013 15:29:17 CET
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
#include "motors.h"
#include "linesensors.h"


// Various utils
#include "utils.h"

#include "defines.h"

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

int main(void) {
	init_adc();
	init_usart();
	init_motors();
//	init_linesensors();
	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Enable interrupts
	sei();

	for(;;) {
		printf("0: %i 1: %i\n", ad_value[0], ad_value[1]);
		if(ad_value[0] > ATT_THRESH || ad_value[1] > ATT_THRESH ){
			set_heading(255,0);
			_delay_ms(100);
		}
		if(ad_value[1] > (ad_value[0] + 20)) {
			set_heading(FULL_SPEED,((ad_value[0] + ad_value[1]) + 100));
			_delay_ms(100);
		}
		else if(ad_value[0] > (ad_value[1] +20)) {
			set_heading(FULL_SPEED,-((ad_value[0] + ad_value[1]) + 100));
			_delay_ms(100);
		}
		else {
			set_heading(BASE_SPEED,40);
			_delay_ms(200);
		}
	}
}
