/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : ons 30 jan 2013 19:43:34
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


// Various utils
#include "utils.h"
#include "macros.h"

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

int main(void) {
	init_adc();
	init_usart();
	//init_motors();
	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Enable interrupts
	sei();

	for(;;) {
		printf("0: %i 1: %i\n", ad_value[0], ad_value[1]);
		if(ad_value[0] > 85){
			set_heading(255,-255);
			_delay_ms(200);
		}
		else if(ad_value[1] > 85){
			set_heading(255,255);
			_delay_ms(200);
		}
		else {
			set_heading(100,0);
			_delay_ms(200);
		}
		
	}
}
