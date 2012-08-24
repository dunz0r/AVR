#define F_CPU 1600000UL /* 16Mhz crystal */

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

/* Funtion prototype */
int set_PORTB_bit(int position, int value);

int main (void)
{
	/* Set port B 3 and 4 as outputs */
	DDRB = 0b000011000;

	// Until the end of the world, do stuff
	while(1)
	{
		
		/* Set 3 to high */
		set_PORTB_bit(5, 1);

		_delay_ms(100);

		set_PORTB_bit(5, 0);
		
		_delay_ms(200);
	}
	return 1;
}

/* Sets value at position on PORTB */
int set_PORTB_bit(int position, int value)
{
	/* Sets or clears the bit in position 'position'
	 * Either 1 or 0 to match 'value'
	 * Leaves all the other bits in PORTB unchanged.
	 */
	if (value == 0)
	{
		PORTB &= ~(1 << position); /* Set the position low */
	}
	else
	{
		PORTB |= (1 << position); /* Set high, leave others alone */
	}

	return 1;
}
