/*
 * Gabriel Fornaeus, 2012
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

