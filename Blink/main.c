#define F_CPU 16000000UL /* 1Mhz internal Oscillator */

#include <avr/io.h>
#include <util/delay.h>

/* Function for long delay */
void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

int main (void)
{
	/* PA0 is digital output */
	DDRB = 0xff;
	asm("NOP");

	/* Loop forever */
	while (1)
	{
		PORTB = 0xff;
		asm("NOP");
		_delay_ms(1000);
		PORTB = 0x00;
		asm("NOP");
		_delay_ms(1000);
	}
	return 0;
}
