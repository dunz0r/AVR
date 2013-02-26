/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : tis 26 feb 2013 15:17:43
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

// Startmodule from http://startmodule.com
#include "startpin.h"

// LEDs
#include "leds.h"

// Various utils
#include "utils.h"

// Various speeds, delays and such
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
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]) && !is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]))
		state = 2;
	// Right sensor is above NEAR_THRESH and left is below
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]) && !is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]))
		state = 3;
	// Both sensors are above NEAR_THRESH
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]) && is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]))
		state = 4;
	// Left sensor is above FAR_THRESH and right sensor is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 5;
	// Right sensor is above FAR_THRESH and left sensor is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]))
		state = 6;
	// Both sensors are above FAR_THRESH
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 7;
	// None of the sensors are above any threshhold
	else
		state = 8;
	return state;
}
/*}}}*/

/*{{{ Behaviours */
void search(void) {
	//set_heading(BASE_SPEED, 30);
	set_motors(0,0);
	_delay_ms(STATE_DELAY);
}

void hunt_far_both(void) {
	set_heading(BASE_SPEED, 0);
	_delay_ms(STATE_DELAY);
}

void hunt_far_left(void) {
	set_heading(BASE_SPEED, -20);
	_delay_ms(STATE_DELAY);
}


void hunt_far_right(void) {
	set_heading(BASE_SPEED, 20);
	_delay_ms(STATE_DELAY);
}

void hunt_near_left(void) {
	set_heading(FULL_SPEED, -120);
	_delay_ms(STATE_DELAY);
}

void hunt_near_right(void) {
	set_heading(FULL_SPEED, 120);
	_delay_ms(STATE_DELAY);
}

void hunt_near_both(void) {
	set_heading(FULL_SPEED, 0);
	_delay_ms(STATE_DELAY);
}


void attack(void) {
	set_heading(FULL_SPEED, 0);
	_delay_ms(STATE_DELAY);
}
/*}}}*/

/*{{{ Main function */
int main(void) {
	/*{{{ Init stuff */
	init_adc();
	init_usart();
	init_motors();
//	init_linesensors();
	init_startpin();
	init_leds();

	// Enable global interrupts
	sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;
	/*}}}*/

	for(;;) {

		binary_led(0);
		/*
		uint8_t state = find_state();
		switch(state) {
			case 1:
				printf("Attack\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				attack();
				break;
			case 2:
				printf("Hunt near left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_left();
				break;
			case 3:
				printf("Hunt near right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_right();
				break;
			case 4:
				printf("Hunt near both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_right();
				break;
			case 5:
				printf("Hunt far left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_left();
				break;
			case 6:
				set_heading(BASE_SPEED, 60);
				printf("Hunt far right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_right();
				break;
			case 7:
				printf("Hunt far both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_both();
				break;
			case 8:
				printf("Search\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				search();
				break;
		}
		*/

	}
}
/*}}}*/
