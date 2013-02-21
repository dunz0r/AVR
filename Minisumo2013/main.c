/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : tor 21 feb 2013 05:28:28
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

/*{{{ Read sensors and decide on state */
uint8_t find_state(void) {
	uint8_t state;
	// Any of the sensors are above ATT_THRESH, they'll never reach 700
	if(is_within_range(700, ATT_THRESH, ad_value[0]) || is_within_range(700, ATT_THRESH, ad_value[1]))
		state = 1;
	// Left sensor is above NEAR_THRESH and right is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 2;
	// Right sensor is above NEAR_THRESH and left is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]))
		state = 3;
	// Both sensors are above NEAR_THRESH
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 4;
	// Left sensor is above FAR_THRESH and right sensor is below
	else if(is_within_range(FAR_THRESH, 0, ad_value[0]) && !is_within_range(FAR_THRESH, 0, ad_value[1]))
		state = 5;
	// Right sensor is above FAR_THRESH and left sensor is below
	else if(is_within_range(FAR_THRESH, 0, ad_value[1]) && !is_within_range(FAR_THRESH, 0, ad_value[0]))
		state = 6;
	// Both sensors are above FAR_THRESH
	else if(is_within_range(FAR_THRESH, 0, ad_value[0]) && is_within_range(FAR_THRESH, 0, ad_value[1]))
		state = 7;
	// None of the sensors are above any threshhold
	else
		state = 8;
	return state;
}
/*}}}*/

/*{{{ Behaviours */
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
/*}}}*/

/*{{{ Main function */
int main(void) {
	/*{{{ Init stuff */
	init_adc();
	init_usart();
	init_motors();
//	init_linesensors();

	// Enable global interrupts
	sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;
	/*}}}*/

	for(;;) {
		uint8_t state = find_state();
		switch(state) {
			case 1:
				printf("Attack\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
				break;
			case 2:
				printf("Hunt near left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
			//	hunt_far_right();
				break;
			case 3:
				printf("Hunt near right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
			//	hunt_near_left();
				break;
			case 4:
				printf("Hunt near both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
			//	hunt_near_right();
				break;
			case 5:
				printf("Hunt far left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
			//	attack();
				break;
			case 6:
				printf("Hunt far right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
				break;
			case 7:
				printf("Hunt far both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
				break;
			case 8:
				printf("Search\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				_delay_ms(500);
				break;
		}

	}
}
/*}}}*/
