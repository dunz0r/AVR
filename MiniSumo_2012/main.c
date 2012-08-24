#define F_CPU 16000000UL /* 16Mhz external crystals */
#include <avr/io.h>
#include <util/delay.h>

/* =====================
 * Defines for pins
 * =====================
 */
#define LED PB5

/* =====================
 * Macros
 * =====================
 */
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= ~(1<<pin)
#define set_input(portdir,pin) portdir &= (1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

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
	set_output(DDRB, 5);
	while(1)
	{
		PORTB = 0xff;
		delay_ms(1000);
		PORTB = 0x00;
		delay_ms(1000);
	}

}
