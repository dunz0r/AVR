/*
 * File Name : adc.c
 * Purpose : Init ADC and read ADC
 * Creation Date : 15-10-2012
 * Last Modified : sön 28 okt 2012 15:07:21
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "adc.h"

// Global variables

// adc_value is an array that contains all the AD values
volatile unsigned char adc_value[NR_AD_CHANNEL];
// Local value
volatile unsigned char ad_count = 0;

void init_adc(void)
{
	// Select Vref=AVCC and left adjusted for 8-bit resolution
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	
	// AD enable, AD interrupt enable and clk/128 prescaling
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

	// Prepares first AD channel
	ADMUX &= 0b11111000;

	// Starts the first conversion
	ADCSRA |=(1<<ADSC);
}

// Interrupt that save the converted value to the array of values
// and starts a new conversion
int ISR(ADC_vect)
{
	adc_value[ad_count]=ADCH;

	if(ad_count<(NR_AD_CHANNEL-1))
		ad_count++;
	else
		ad_count=0;
}


uint16_t read_adc(uint8_t adc_channel)
{
	// Select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0 ) | (adc_channel & 0x0F);
	// Single conversion mode
	ADCSRA |=(1<<ADSC);
	// Wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}
