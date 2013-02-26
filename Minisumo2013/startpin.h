/*
 * File Name : startpin.h
 * Purpose : Startmodule
 * Creation Date : 26-02-2013
 * Last Modified : tis 26 feb 2013 01:11:59
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#ifndef STARTPIN_H
#define STARTPIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"
#include <util/delay.h>

void init_startpin(void);
#endif
