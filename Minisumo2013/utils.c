/*
 * File Name : constrain.c
 * Purpose : Various utilities
 * Creation Date : 2013-01-16
 * Last Modified : Wed 16 Jan 2013 21:30:36 CET
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include <stdint.h>
#include "utils.h"
/*{{{ Subtracts and adds with overflow protection */
int16_t constrain(int16_t high, int16_t  low, int16_t  x) {
	if(x > high) x = high;
	if(x < low) x = low;
	return x;
}
/*}}}*/
