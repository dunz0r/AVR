/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
<<<<<<< HEAD
 * Last Modified : mån 18 mar 2013 22:57:50
=======
 * Last Modified : mån 18 mar 2013 22:57:50
>>>>>>> 60260805c406807d406ca70e0bc26a862f03c711
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// Serial send
#include "usart.h"

// Button for selecting strategy
#include "switch.h"

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
#include "constants.h"

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

/*{{{ Read sensors and decide on state */
uint8_t find_state(void) {
	uint8_t state;
	// Any of the sensors are above ATT_THRESH
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
	return state;
}
/*}}}*/

/*{{{ Behaviours */
void left_turn(void) {
	set_motors(255,-255);
	_delay_ms(200);
}

void right_turn(void) {
	set_motors(-255,255);
	_delay_ms(200);
}

void full_turn(void) {
	set_motors(-255,255);
	_delay_ms(350);
}

void reverse(void) {
	set_motors(-255,-255);
	_delay_ms(200);
}

void search(void) {
	set_heading(255, (ad_value[0] - ad_value[1]) * 3);
	_delay_ms(STATE_DELAY);
}

void hunt_far_both(void) {
	set_heading(255, (ad_value[0] - ad_value[1]) * 2);
	/*
	if(ad_value[0] == ad_value[1])
		set_heading(BASE_SPEED, 0);
	else if(ad_value[0] > ad_value[1])
		set_heading(BASE_SPEED, 40);
	else if(ad_value[1] > ad_value[0])
		set_heading(BASE_SPEED, -40);
		*/
	_delay_ms(STATE_DELAY);
}

void hunt_far_left(void) {
	set_heading(BASE_SPEED, -70);
	_delay_ms(STATE_DELAY);
}


void hunt_far_right(void) {
	set_heading(BASE_SPEED, 70);
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
	set_heading(255, (ad_value[0] - ad_value[1]));
	/*
	if(is_within_range(ad_value[0]+5, ad_value[0]-5, ad_value[1]) ||
			is_within_range(ad_value[0]+5, ad_value[0]-5, ad_value[1]))
		set_heading(FULL_SPEED, 0);
	else if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, 130);
	else if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, -130);
	_delay_ms(STATE_DELAY);
	*/
}

void attack(void) {
	set_heading(FULL_SPEED, 0);
	_delay_ms(STATE_DELAY);
}
/*}}}*/

/*{{{ Main function */
int main(void) {

	// The start module is slow 1/10, just to be sure
	_delay_ms(30);
	// Disable global interrupts during start sequence
	cli();
	uint8_t strategy = 1;
	init_adc();
	init_usart();
	init_motors();
	init_sidesensors();
	init_leds();
	init_startpin();
	//init_linesensors();
	// Wait for startpin to go high
	while(!(PINB & (1 << PB1))){
		binary_led(strategy);
		set_motors(0,0);
		// Read the button and cycle through strategys
		if(switch_is_pressed()){
			strategy++;
			if(strategy > 6)
				strategy = 1;
			_delay_ms(200);
		}
	}

	// Enable global interrupts
	sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Perform starting strategy
	switch(strategy) {
		case 1:
			left_turn();
			break;
		case 2:
			right_turn();
			break;
		case 3:
			full_turn();
			break;
		case 4:
			reverse();
			right_turn();
			break;
		case 5:
			reverse();
			left_turn();
			break;
		case 6:
			reverse();
			full_turn();
			break;
		}

	for(;;) {

		// If the side sensors trigger and the attack sensors are below ATT_THRESH
		if(!(PINB & (1 << PB4)))
			left_turn();
		if(!(PINB & (1 << PB5)))
			right_turn();
		
		if(ad_value[0] > ATT_THRESH || ad_value[1] > ATT_THRESH)
			set_heading(255,0);

		//set_heading(255, (ad_value[0] - ad_value[1])*3);
		// Decide which state the sensors are in
		uint8_t state = find_state();
		// Show state on 3-bit display
		binary_led(state);
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
				hunt_near_both();
				break;
			case 4:
				printf("Hunt far left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt_far_left();
				break;
			case 5:
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
