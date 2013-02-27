/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : ons 27 feb 2013 09:38:06
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// Serial send
#include "usart.h"

// ADC with interrupts
#include "adc.h"

// Motor control
#include "motors.h"

// Front mounted CNY70 linesensors
#include "linesensors.h"

// Side mounted Sharp 10cm digital sensors
#include "sidesensors.h"

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
	if(is_within_range(700, ATT_THRESH, ad_value[0]) || is_within_range(700, ATT_THRESH, ad_value[1]))
		state = 0;
	// Left sensor is above NEAR_THRESH and right is below
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]) && !is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]))
		state = 1;
	// Right sensor is above NEAR_THRESH and left is below
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]) && !is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]))
		state = 2;
	// Both sensors are above NEAR_THRESH
	else if(is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[0]) && is_within_range(ATT_THRESH, NEAR_THRESH, ad_value[1]))
		state = 3;
	// Left sensor is above FAR_THRESH and right sensor is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 4;
	// Right sensor is above FAR_THRESH and left sensor is below
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]) && !is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]))
		state = 5;
	// Both sensors are above FAR_THRESH
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 6;
	// None of the sensors are above any threshhold
	else
		state = 7;
	// Show state on 3-bit displat
	binary_led(state);
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

	init_leds();
	/*{{{ Wait for startpin to go high */
	while(!(PINB & (1 << PB1))){
		set_motors(0,0);
		binary_led(2);
		_delay_ms(50);
		binary_led(4);
		_delay_ms(50);
	}
	/*}}}*/

	/*{{{ Init stuff */
	init_adc();
	init_usart();
	init_motors();
	init_sidesensors();
	//init_linesensors();
	init_startpin();

	// Enable global interrupts
	sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;
	/*}}}*/

	for(;;) {

		// Turn to either side if sidesensors trigger
		if(PIND & (1 << PB4)){
			set_motors(0,-190);
			_delay_ms(200);
		}
		if(PIND & (1 << PB5)){
			set_motors(0,190);
			_delay_ms(200);
		}

		uint8_t state = find_state();
		switch(state) {
			case 0:
				printf("Attack\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				attack();
				break;
			case 1:
				printf("Hunt near left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_left();
				break;
			case 2:
				printf("Hunt near right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_right();
				break;
			case 3:
				printf("Hunt near both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_near_right();
				break;
			case 4:
				printf("Hunt far left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_left();
				break;
			case 5:
				set_heading(BASE_SPEED, 60);
				printf("Hunt far right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_right();
				break;
			case 6:
				printf("Hunt far both\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_both();
				break;
			case 7:
				printf("Search\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				search();
				break;
		}

	}
}
/*}}}*/
