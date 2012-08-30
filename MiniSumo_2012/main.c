/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : tor 30 aug 2012 17:12:13
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
/*{{{ Includes */
#include <avr/interrupt.h>
#include "macros.h"
#include "usart.h"
#include "delay_ms.h"
/*}}}*/

/*{{{ Defines for pins*/
#define LED 5,B
#define LED2 6,D
#define VREF 5
#define POT 1000
/*}}}*/

/*{{{ Initliaze TIMER1*/
void init_timer1(void)
{
	/* Set initial timer value */
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 |= (1 << TOIE1); /* Enable timer overflow interrupt */
	TCCR1B |= (1 << CS12); /* Prescaler at 1024 */
	sei();
}
/*}}}*/

/*{{{ Main function */
int main (void)
{
	double vbg, potval;
	set_output(LED2);
	set_output(LED);
	usart0_init();
	//set stream pointer
	FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

	// assign our stream to standard I/O streams
	stdout=&usart0_str;

	for(;;)
	{
		if (potval > 128) {
			output_low(LED);
			output_high(LED2);
		}
		else if(potval < 128) {
			output_low(LED2);
			output_high(LED);
		}
		// reading potentiometer value and recalculating to ohms
		// sending potentiometer value to terminal
		printf("Potval = %u Ohms \n", (uint16_t)potval);
		// reading band gap voltage and recalculating to volts
		vbg=(double)VREF/1024;
		// Printing value to terminal
		printf("Vbg = %4.2fV\n", vbg);
		_delay_ms(255);
		_delay_ms(255);
		_delay_ms(255);
		_delay_ms(255);

	}

}
/*}}}*/

/*
   ISR(TIMER1_OVF_vect)
   {
   toggle_output(LED);
   }
   */
