/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : Fri 15 Feb 2013 03:09:41 CET
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

uint8_t find_state(void) {
	uint8_t state;
	// Left sensor is above FAR_THRESH and right sensor is below
	if(ad_value[0] > FAR_THRESH && ad_value[1] < FAR_THRESH)
		state = 1;
	// Right sensor is above FAR_THRESH and left sensor is below
	if(ad_value[1] > FAR_THRESH && ad_value[0] < FAR_THRESH)
		state = 2;
	// Right sensor is above NEAR_THRESH and left is below
	if(ad_value[0] > NEAR_THRESH && ad_value[1] < NEAR_THRESH)
		state = 3;
	// Left sensor is above NEAR_THRESH and right is below
	if(ad_value[1] > NEAR_THRESH && ad_value[0] < NEAR_THRESH)
		state = 4;
	// Any of the sensors are above ATT_THRESH
	if(ad_value[0] > ATT_THRESH || ad_value[1] > ATT_THRESH)
		state = 5;
	// None of the sensors are above any threshhold
	if(ad_value[0] < FAR_THRESH && ad_value[1] < FAR_THRESH)
		state = 6;
	return state;
}




int main(void) {
	init_adc();
	init_usart();
	init_motors();
	init_linesensors();
	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Enable interrupts
	sei();

	uint8_t state;
	for(;;) {
		state = find_state();
	}
}
