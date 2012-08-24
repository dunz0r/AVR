#include <avr/io.h>


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
void delay_ms(uint8_t x); /* General purpose delay */

/* =====================
 * Main function
 * =====================
 */
int main (void)
{
	/* Until the end of the world, do stuff */
	set_output(DDRB,LED);
	while(1)
	{
		
		delay_ms(200);
		delay_ms(200);

		/* Set 5 to high */
		output_high(DDRB,LED);

		delay_ms(200);
		delay_ms(200);
		delay_ms(200);

		output_low(DDRB,LED);
	}
	return 1;
}

/* =====================
 * Kills time in a calibrated manner
 * =====================
 */
void delay_ms(uint8_t ms)
{
	uint16_t delay_count = F_CPU / 17500;

	while (ms != 0)
	{
		int i = 0;
		for (i=0; i != delay_count; i++);
		ms--;
	}
}
