/*
 * File Name : adc.c
 * Purpose : Init ADC and read ADC
 * Creation Date : 15-10-2012
 * Last Modified : mån 15 okt 2012 01:51:08
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#include "adc.h"
void init_adc(void)
{
	// Select Vref=AVCC
	ADMUX |= (1<<REFS0);
	// Set prescaler to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
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
