/*
 * File Name : motors.c
 * Purpose : Control of motors via an L298N H-bridge
 * Creation Date : 2013-01-16
 * Last Modified : lör 23 mar 2013 13:35:26
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
	DDRB |= (1 << 0); // INPUT_1
	DDRD |= (1 << 7); // INPUT_2
	DDRB |= (1 << 3); // INPUT_3
	DDRD |= (1 << 4); // INPUT_4

	DDRD |= (1 << 5); // ENABLE_A
	DDRD |= (1 << 6); // ENABLE_B

	// Clear OC0A and OC0B on compare match
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
	if(RUN_MOTORS) {
		// Set motor speeds
		// Forward
		if(left_motor < 0) {
			// Set INPUT1, INPUT2 for reverse
			PORTB &= ~(1 << 0);
			PORTD |= (1 << 7);
			ENABLE_A = -(left_motor);
		}
		// Reverse
		if(left_motor > 0) {
			// Set INPUT1, INPUT2 for forward
			PORTB |= (1 << 0);
			PORTD &= ~(1 << 7);
			ENABLE_A = left_motor;
		} else if(left_motor == 0) { // Stop
			PORTB &= ~(1 << 0);
			PORTD &= ~(1 << 7);
			ENABLE_A = 1;
		}
		
		// Forward
		if(right_motor > 0) {
			// Set INPUT4, INPUT3 for reverse
			PORTB &= ~(1 << 3);
			PORTD |= (1 << 4);
			ENABLE_B = right_motor;
		}
		// Reverse
		if(right_motor < 0) {
			// Set INPUT3, INPUT4 for forward
			PORTD &= ~(1 << 4);
			PORTB |= (1 << 3);
			ENABLE_B = -(right_motor);
		} else if(right_motor == 0) { // Stop
			PORTD &= ~(1 << 4);
			PORTB &= ~(1 << 3);
			ENABLE_B = 1;
		}
	}
}
/*}}}*/
