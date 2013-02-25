/*
 * File Name : utils.c
 * Purpose : Various utilities
 * Creation Date : 2013-01-16
 * Last Modified : mån 25 feb 2013 22:18:55
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <stdint.h>
#include "utils.h"
/*{{{ Constrains with overflow protection */
int16_t constrain(int16_t high, int16_t  low, int16_t  value) {
	if(value > high) value = high;
	if(value < low) value = low;
	return value;
}
/*}}}*/

/*{{{ Returns true if a value is within range */
char is_within_range(int16_t high, int16_t  low, int16_t  value) {
	char output;
	if(value >= low && value <= high) output = 1;
	else output = 0;
	return output;
}
/*}}}*/

/*{{{ convert a value from millimeters to "sharp" */
uint16_t sharp_to_mm(uint16_t sharp){
	uint16_t millimeters = ( 2914 / (sharp + 5))-1;
	return millimeters;
}
/*}}}*/
