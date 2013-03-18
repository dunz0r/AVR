/*
 * File Name : constants.h
 * Purpose : Defined constants etc
 * Creation Date : 10-02-2013
 * Last Modified : mån 18 mar 2013 22:53:05
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef DEFINE_H

// If the surface is black
#define ON_BLACK 0

// Distance threshholds
#define FAR_THRESH 110
#define NEAR_THRESH 160
#define ATT_THRESH 300

// Speeds
#define LOW_SPEED (BASE_SPEED / 1.5)
#define BASE_SPEED (FULL_SPEED * 0.6)
#define FULL_SPEED 255

// Times
//#define STATE_DELAY 60
#define STATE_DELAY (FULL_SPEED / 5)


#endif
