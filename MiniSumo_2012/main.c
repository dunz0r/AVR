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
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
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
	set_output(DDRB, LED);
	while(1)
	{
		output_high(PORTB, PB5);
		delay_ms(1000);
		output_low(PORTB, PB5);
		delay_ms(1000);
	}

}
