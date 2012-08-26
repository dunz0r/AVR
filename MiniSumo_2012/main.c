/* =====================
 * Gabriel Fornaeus, 2012
 * =====================
 */
#include <avr/io.h>
#include <util/delay.h>
#include "iomacros.h"

/* =====================
 * Defines for pins
 * =====================
 */
#define LED 5,B

void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

/* =====================
 * Main function
 * =====================
 */
int main (void)
{
	out(LED);
	while(1)
	{
		output_high(LED);
		delay_ms(1000);
		output_low(LED);
		delay_ms(1000);
	}

}
