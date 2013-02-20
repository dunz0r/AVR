/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : Sun 17 Feb 2013 16:50:49 CET
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <util/delay.h>
#include <avr/io.h>
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
	// Left sensor is above NEAR_THRESH and right is below
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

void wander(void) {
	printf("Wander\n");
}

void hunt_far_left(void) {
	printf("Hunt far left\n");
}


void hunt_far_right(void) {
	printf("Hunt far right\n");
}

void hunt_near_left(void) {
	printf("Hunt near left\n");
}

void hunt_near_right(void) {
	printf("Hunt near right\n");
}

void attack(void) {
	printf("Attack\n");
}


int main(void) {

    init_adc();
	init_usart();
	init_motors();
	init_linesensors();
	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Enable global interrupts
	sei();

	for(;;) {
		uint8_t state = find_state();
		switch(state) {
			case 1:
				hunt_far_left();
				break;
			case 2:
				hunt_far_right();
				break;
			case 3:
				hunt_near_left();
				break;
			case 4:
				hunt_near_right();
				break;
			case 5:
				attack();
				break;
			case 6:
				wander();
				break;
		}

	}
}
