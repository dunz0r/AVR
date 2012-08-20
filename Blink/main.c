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
    DDRB |= _BV (DDB5);

    /* Loop forever */
    while (1)
    {
        PORTB &= ~_BV(DDB5);
        delay_ms(1000);

        PORTB |= _BV(DDB5);
        delay_ms(1000);
    }
}
