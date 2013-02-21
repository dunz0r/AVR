/*
 * File Name : constrain.c
 * Purpose : Various utilities
 * Creation Date : 2013-01-16
 * Last Modified : tor 21 feb 2013 05:11:40
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

char is_within_range(int16_t high, int16_t  low, int16_t  value) {
	char output;
	if(value < high && value > low) output = 1;
	else output = 0;
	return output;
}
/*}}}*/
