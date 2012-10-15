/*
 * File Name : adc.h
 * Purpose : Init and read ADC
 * Creation Date : 15-10-2012
 * Last Modified : mån 15 okt 2012 01:49:02
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
/* Header guard */
#ifndef ADC_H

#define ADC_H
#include <stdio.h>
#include <avr/io.h>

void init_adc(void);
uint16_t read_adc(uint8_t adc_channel);
#endif
