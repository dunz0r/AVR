/*
 * File Name : adc.h
 * Purpose : Init and read ADC
 * Creation Date : 15-10-2012
 * Last Modified : sön 11 nov 2012 21:46:05
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
/* Header guard */
#ifndef ADC_H

#define ADC_H
#include <stdio.h>
#include <avr/io.h>

#define NR_AD_CHANNEL 1
// Global variables
//
// adc_value is an array that contains all the AD values
volatile unsigned char adc_value[NR_AD_CHANNEL];

void init_adc(void);
uint16_t read_adc(uint8_t adc_channel);
#endif
