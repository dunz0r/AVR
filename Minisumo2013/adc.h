/*
 * File Name : adc.h
 * Purpose : Header for the adc stuff
 * Creation Date : 2013-01-08
 * Last Modified : ons 24 apr 2013 20:15:23
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#ifndef ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
// The number of ADC channels we have
#define NR_AD_CHANNEL 2

// ad_value is an array that contains all the ad values
volatile uint16_t ad_value[NR_AD_CHANNEL];

// Initializing the Analog converter and starts the first one.
// After that it will run by it self via interrupts.
void init_adc(void);

#endif
