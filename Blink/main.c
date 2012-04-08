/*
 Blink an LED
 By Gabriel Fornaeus <gf@hax0r.se>

 */
#include <avr/io.h>
#include <util/delay.h>

// Define functions
//======================
void ioinit(void); // Initialises IO
//======================

int main(void)
{
        ioinit(); // Setup IO pins and defaults
        while(1) {
                PORTC = 0xFF;
                PORTB = 0xFF;
                PORTD = 0xFF;
                _delay_ms(500);

                PORTC = 0x00;
                PORTB = 0x00;
                PORTD = 0x00;
                _delay_ms(500);
        }
        return 0;
}

void ioinit (void)
{
        //1 = output, 0 = input
        DDRB = 0b11111111; //All outputs
        DDRC = 0b11111111; //All outputs
        DDRD = 0b11111110; //PORTD (RX on PD0)
}
