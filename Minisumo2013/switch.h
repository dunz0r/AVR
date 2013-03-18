/*
 * File Name : switch.h
 * Purpose : Reads a switch
 * Creation Date : 18-03-2013
 * Last Modified : mån 18 mar 2013 17:57:16
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>

void init_switch(void);

uint8_t switch_is_pressed(void);
#endif
