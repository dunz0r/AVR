/*
 * File Name : constants.h
 * Purpose : Defined constants etc
 * Creation Date : 10-02-2013
 * Last Modified : lör 23 mar 2013 17:58:29
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef DEFINE_H

// If the surface is black
#define ON_BLACK 0

// Stop or run motors
#define RUN_MOTORS 1

// Distance threshholds
#define FAR_THRESH 110
#define NEAR_THRESH 160
#define ATT_THRESH 300

// Speeds
#define LOW_SPEED (FULL_SPEED * 0.4)
#define BASE_SPEED (FULL_SPEED * 0.6)
#define FULL_SPEED 255

// Times
//#define STATE_DELAY 60
#define STATE_DELAY (FULL_SPEED / 5)


#endif
