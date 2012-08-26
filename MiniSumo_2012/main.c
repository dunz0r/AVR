/*
 * File Name : main.c
 * Purpose :
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 03:54:54
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

/*
 * Defines for pins
 *
 */
#define LED 5,B

/*
 * Function prototypes
 *
 */
void delay_ms(uint16_t ms);

/*
 * Main function
 *
 */
int main (void)
{
	set_output(LED);
	while(1)
	{
		output_high(LED);
		delay_ms(1000);
		output_low(LED);
		delay_ms(1000);
	}
}

/*
 * For longer delays
 *
 */
void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

