/*
 * File Name : main.c
 * Purpose : test adc
 * Creation Date : 2012-12-30
 * Last Modified : fre 19 jul 2013 22:04:40
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

// Timer1
#include "timer.h"

// Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

/* This is a global variable to keep track on if we should do a full turn on line
 * sensor hit or not */
volatile uint8_t linehit_counter = 0;

/*{{{ Read sensors and decide on state */
uint8_t find_state(void) {
	uint8_t state;
	// Any of the sensors are above ATT_THRESH
	if(is_within_range(700, ATT_THRESH, ad_value[0])
			|| is_within_range(700, ATT_THRESH, ad_value[1]))
		state = 0;
	// Both sensors are above FAR_THRESH
	else if(is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[0]) && is_within_range(NEAR_THRESH, FAR_THRESH, ad_value[1]))
		state = 1;
	// None of the sensors are above any threshhold
	else
		state = 2;
	return state;
}
/*}}}*/

/*{{{ Behaviours */
void stop(void)  {
	while(!(PINB & (1 << PB1))) {
		cli();
		// "Break"
		set_motors(-1,-1);
		_delay_ms(5);
		// Stop
		set_motors(0,0);
		int i;
		for (i = 0; i < 7; i++) {
			binary_led(i);
			_delay_ms(100);
		}
	}
}

void left_turn(void) {
	set_motors(FULL_SPEED,-(FULL_SPEED));
	_delay_ms(STATE_3);
	set_motors(FULL_SPEED, FULL_SPEED);
}

void right_turn(void) {
	set_motors(-(FULL_SPEED),FULL_SPEED);
	_delay_ms(STATE_3);
	set_motors(FULL_SPEED, FULL_SPEED);
}

void full_turn(void) {
	set_motors(-FULL_SPEED,FULL_SPEED);
	_delay_ms(STATE_4);
	set_motors(FULL_SPEED, FULL_SPEED);
}

void avoidance_move(void) {
	set_motors(-(FULL_SPEED), -(LOW_SPEED));
	_delay_ms(STATE_DELAY);
	set_motors(-(FULL_SPEED), -(FULL_SPEED));
	_delay_ms(STATE_DELAY);
	set_motors(FULL_SPEED, FULL_SPEED);
}

void reverse(void) {
	set_motors(-(FULL_SPEED),-(FULL_SPEED));
	_delay_ms(STATE_3);
}

void search(void) {
	if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, 180);
	else
		set_heading(FULL_SPEED, -180);
	_delay_ms(STATE_DELAY);
}

void hunt_far_both(void) {
	set_heading(FULL_SPEED, (ad_value[0] - ad_value[1]) * 2);
	if(ad_value[0] == ad_value[1])
		set_heading(BASE_SPEED, 0);
	else if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, 130);
	else if(ad_value[1] > ad_value[0])
		set_heading(FULL_SPEED, -130);
	_delay_ms(STATE_DELAY);
}

void hunt_far_left(void) {
	set_heading(FULL_SPEED, -180);
	_delay_ms(STATE_DELAY);
}


void hunt_far_right(void) {
	set_heading(FULL_SPEED, 180);
	_delay_ms(STATE_DELAY);
}

void hunt_near_left(void) {
	set_heading(FULL_SPEED, -220);
	_delay_ms(STATE_DELAY);
}

void hunt_near_right(void) {
	set_heading(FULL_SPEED, 220);
	_delay_ms(STATE_DELAY);
}

void hunt_near_both(void) {
	set_heading(FULL_SPEED, (ad_value[0] - ad_value[1]) * 2);
	if(is_within_range(ad_value[0]+5, ad_value[0]-5, ad_value[1]) ||
			is_within_range(ad_value[0]+5, ad_value[0]-5, ad_value[1]))
		set_heading(FULL_SPEED, 0);
	else if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, 150);
	else if(ad_value[0] > ad_value[1])
		set_heading(FULL_SPEED, -150);
	_delay_ms(STATE_DELAY);
}

void hunt(void) {
	int8_t ad_diff = ad_value[0] - ad_value[1];
	set_heading(FULL_SPEED, (ad_diff * 2));
	_delay_ms(STATE_DELAY);
}

void attack(void) {
	start_timer1();
	set_heading(FULL_SPEED, 0);
	_delay_ms(STATE_DELAY);
}
/*}}}*/

/* {{{ Strategy selector */
void perform_strategy(uint8_t strategy) {
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
		case 7:
			reverse();
			break;
	}
}

/* }}} */

/*{{{ Main function */
int main(void) {

	// Short startup delay to make sure that the startmodule has initialized
	// Disable global interrupts during start sequence
	cli();
	uint8_t strategy = 1;
	init_adc();
	init_usart();
	init_motors();
	init_sidesensors();
	init_leds();
	init_timer1();
	init_timer2();
//	init_startpin();
	init_linesensors();
	set_motors(0,0);
	for (int i = 0; i < 7; i++) {
		binary_led(i);
		_delay_ms(100);
	}
	// Wait for startpin to go high
	/*
	while(!(PINB & (1 << PB1))){
		//binary_led(strategy);
		set_motors(0,0);
		// Read the button and cycle through strategys
		if(switch_is_pressed()){
			strategy++;
			if(strategy > 7)
				strategy = 1;
			_delay_ms(250);
		}
	}
	*/

	// Enable global interrupts
	sei();

	// Assign our stream to standard I/O streams
	stdout=&usart0_str;

	// Perform starting strategy
	perform_strategy(strategy);

	for(;;) {
		// If the side sensors trigger and the attack sensors are below ATT_THRESH

		// Decide which state the sensors are in
		uint8_t state = find_state();
		// Show state on 3-bit display
		binary_led(state);
		// Stop timer1 if we're not attacking
		if(state != 0){
			stop_timer1();
			if(!(PINB & (1 << PB4)))
				left_turn();
			if(!(PINB & (1 << PB5)))
				right_turn();
		}

		switch(state) {
			case 0:
				printf("Attack\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				attack();
				break;
			case 1:
				printf("Hunt near left\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				hunt();
				break;
			case 2:
				printf("Hunt near right\t0: %i 1: %i\n", ad_value[0], ad_value[1]);
				search();
				break;
		}
	}
}
/*}}}*/

/*{{{ ISRs */
// When the timer triggers, make J-turn
ISR (TIMER1_COMPA_vect) {
	binary_led(2);
	avoidance_move();
}

ISR (TIMER2_COMPA_vect) {
	linehit_counter = 0;
}

/*
ISR(PCINT0_vect) {
	stop();
}
*/

ISR (INT0_vect) {
	binary_led(3);
	set_motors(-255,-255);
	_delay_ms(STATE_4);
	left_turn();
}

ISR (INT1_vect) {
	binary_led(5);
	set_motors(-255,-255);
	_delay_ms(STATE_4);
	right_turn();
}

/*}}}*/
