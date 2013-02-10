/*
 * File Name : adc.c
 * Purpose : Provice adc reading functions
 * Creation Date : 2013-01-08
 * Last Modified : sön 10 feb 2013 22:44:59
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */


#include "adc.h"
// ad_value is an array that contains all the ad values
volatile uint16_t ad_value[NR_AD_CHANNEL];
// Local values
volatile unsigned char ad_count=0;

/*{{{ Initialize adc */
void init_adc(void) {
	//5V AREF
	ADMUX |= (1<<REFS0);
	//| (1<<ADLAR);

	//AD enable, AD interrupt enable and clk/128 prescaling
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	// Prepares first ad channel
	ADMUX &= 0b11110000;

	// Disable digital on the ADC-pins
	DIDR0 = 0x01;

	//Starts the first conversion
	ADCSRA |= (1<<ADSC);
}
/*}}}*/

/* {{{ Interrupts that saves the converted value to the array of values and starts a new conversion */
ISR(ADC_vect){
	ad_value[ad_count]=ADC;

	if(ad_count<(NR_AD_CHANNEL-1))
		ad_count++;
	else
		ad_count=0;

	// Select ADC channel with safety mask
	ADMUX = (ADMUX & 0b11110000) | ad_count;
	
	ADCSRA |= (1<<ADSC);
}
/* }}} */
