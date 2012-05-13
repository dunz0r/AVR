#define F_CPU 100000UL /* 1Mhz internal Oscillator */

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

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
    DDRA = _BV (PA0);

    /* Loop forever */
    while (1)
    {
        /* Clear PA0 on PORTA (digital high) and delay for one second */
        PORTA &= ~_BV(PA0);
        delay_ms(1000);

        /* set PA0 on PORTA (digital low) and delay for one second */
        PORTA |= _BV(PA0);
        delay_ms(1000);
    }
}
