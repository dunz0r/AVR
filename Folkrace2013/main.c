/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : tis 23 apr 2013 20:36:48
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// Serial send
#include "usart.h"

// Motor control
#include "motors.h"

// Startmodule from http://startmodule.com
#include "startpin.h"

// Various utils
#include "utils.h"

// Timer1
#include "timer.h"

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

/*{{{ Main function */
int main(void) {

	// Short startup delay to make sure that the startmodule has initialized
	_delay_ms(30);
	// Disable global interrupts during start sequence
	cli();
	uint8_t strategy = 1;
	init_usart();
	init_motors();
	init_timer1();
	init_timer2();
	init_startpin();
		sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;


	for(;;) {
	}
}
/*}}}*/
