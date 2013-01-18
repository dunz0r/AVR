/*
 * File Name : motors.c
 * Purpose : Control of motors via an L298N H-bridge
 * Creation Date : 2013-01-16
 * Last Modified : Fri 18 Jan 2013 05:24:14 CET
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "motors.h"

/*{{{ Set heading based on difference between motors and desired speed */
void set_heading(int16_t speed, uint16_t difference) {
	// Set heading, left = speed + diff, right = speed - diff
	int left = speed + difference;
	left = constrain(255,-255,left);
	int right = speed - difference;
	right = constrain(255,-255,right);
	set_motors(left,right);
}
/*}}}*/

/*{{{ Initialize motor inputs and outputs */
void init_motors(void) {
	
	// Set up DIR bits and enable PWM to output
	set_output(INPUT_1);
	set_output(INPUT_2);
	set_output(INPUT_3);
	set_output(INPUT_4);

	DDRD |= (1 << 5)
	DDRD |= (1 << 6)

	// Clear OC0A and OC0B om compare match
	TCCR0A |= (1 << COM0A1);
	TCCR0A |= (1 << COM0B1);

	// Fast PWM
	TCCR0A |= (1 << WGM00);

	// Prescaler att 64
	TCCR0B |= (1 << CS01);
}
/*}}}*/

/*{{{ Control left and right motor speeds, stop if 0 */
void set_motors(int16_t left_motor, int16_t right_motor) {
	// Set motor speeds
	// Forward
	if(left_motor > 0) {
		// Set INPUT1, INPUT2 for reverse
		output_low(INPUT_1);
		output_high(INPUT_2);
		ENABLE_A = left_motor;
	}
	// Reverse
	if(left_motor < 0) {
		// Set INPUT1, INPUT2 for forward
		output_high(INPUT_1);
		output_low(INPUT_2);
		ENABLE_A = left_motor;
	} else if(left_motor == 0) { // Stop
		output_low(INPUT_1);
		output_low(INPUT_2);
	}
	
	// Forward
	if(right_motor > 0) {
		// Set INPUT1, INPUT2 for reverse
		output_low(INPUT_3);
		output_high(INPUT_4);
	}
	// Reverse
	if(right_motor < 0) {
		// Set INPUT1, INPUT2 for forward
		output_high(INPUT_3);
		output_low(INPUT_4);
		ENABLE_B = right_motor;
	} else if(right_motor == 0) { // Stop
		output_low(INPUT_3);
		output_low(INPUT_4);
	}
}
/*}}}*/
