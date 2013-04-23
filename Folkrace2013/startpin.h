/*
 * File Name : startpin.h
 * Purpose : Startmodule
 * Creation Date : 26-02-2013
 * Last Modified : tis 23 apr 2013 20:43:11
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#ifndef STARTPIN_H
#define STARTPIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motors.h"

void init_startpin(void);
#endif
