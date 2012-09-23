/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : sön 23 sep 2012 17:48:18
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
/*{{{ Includes */
#include <avr/interrupt.h>
#include "macros.h"
#include "usart.h"
#include "delay_ms.h"
#include "timers.h"
/*}}}*/

/*{{{ Defines for pins*/
#define LED 5,B
#define LED2 6,D
#define VREF 5
#define POT 1000
/*}}}*/

/*{{{ Main function */
int main (void)
{
	double vbg, potval;
	potval = 2;
	set_output(LED2);
	set_output(LED);
	usart0_init();
	//set stream pointer
	FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);

	// assign our stream to standard I/O streams
	stdout=&usart0_str;

	for(;;)
	{

	}

}
/*}}}*/

/*
   ISR(TIMER1_OVF_vect)
   {
   toggle_output(LED);
   }
   */

