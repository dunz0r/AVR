/*
 * File Name : leds.h
 * Purpose : Control LEDs
 * Creation Date : 26-02-2013
 * Last Modified : ons 17 jul 2013 16:49:03
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#ifndef LEDS_H
#define LEDS_H
#include <avr/io.h>

void init_leds(void);
void binary_led(uint8_t number);

#endif
