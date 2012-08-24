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

/* =====================
 * Funtion prototypes
 * =====================
 */

/* =====================
 * Main function
 * =====================
 */
int main (void)
{
	set_output(DDRB, 5);
	while(1)
	{
		output_high(PORTB, 5);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		output_low(PORTB, 5);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
	}

}
