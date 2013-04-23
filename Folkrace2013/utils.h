/*
 * File Name : utils.h
 * Purpose : Various utilities
 * Creation Date : 2013-01-16
 * Last Modified : mån 25 feb 2013 22:39:26
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef CONSTRAIN_H

int16_t constrain(int16_t high, int16_t low, int16_t value);

char is_within_range(int16_t high, int16_t low, int16_t value);

#endif
