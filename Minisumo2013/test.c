/*{{{ Subtracts and adds with overflow protection */
int16_t constrain(int16_t high, int16_t  low, int16_t  x) {
	if(x > high) x = high;
	if(x < low) x = low;
	return x;
}
/*}}}*/
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

/*{{{ Control left and right motor speeds, stop if 0 */
void set_motors(int16_t left_motor, int16_t right_motor) {
	// Set motor speeds
	// Forward
	if(left_motor > 0) {
		// Set INPUT1, INPUT2 for reverse
		output_low(INPUT_1);
		output_high(INPUT_2);
		OCR1A=left_motor
	}
	// Reverse
	if(left_motor < 0) {
		// Set INPUT1, INPUT2 for forward
		output_high(INPUT_1);
		output_low(INPUT_2);
		OCR1A=left_motor
	} else if(left_motor == 0) { // Stop
		output_low(INPUT_1);
		output_low(INPUT_2);
		output_low(ENABLE_A);
	}
	
	// Forward
	if(right_motor > 0) {
		// Set INPUT1, INPUT2 for reverse
		output_low(INPUT_3);
		output_high(INPUT_4);
		OCR2B=right_motor
	}
	// Reverse
	if(right_motor < 0) {
		// Set INPUT1, INPUT2 for forward
		output_high(INPUT_3);
		output_low(INPUT_4);
		OCR2B=right_motor
	} else if(right_motor == 0) { // Stop
		output_low(INPUT_3);
		output_low(INPUT_4);
		output_low(ENABLE_B);
	}
}
/*}}}*/
