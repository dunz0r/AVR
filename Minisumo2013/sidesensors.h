/*
 * File Name : sidesensors.h
 * Purpose : Read the digital sharps at the sides of the robot
 * Creation Date : 26-02-2013
 * Last Modified : tor 11 apr 2013 04:30:19
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

#ifndef SIDESENSORS_H
#define SIDESENSORS_H
#include <avr/interrupt.h>

void init_sidesensors(void);

uint8_t left_sensor_triggered(void);
uint8_t right_sensor_triggered(void);
#endif
