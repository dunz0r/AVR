/*
 * File Name : constants.h
 * Purpose : Defined constants etc
 * Creation Date : 10-02-2013
 * Last Modified : tor 11 apr 2013 01:49:09
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef DEFINE_H

// If the surface is black
//#define ON_BLACK 1

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
#define STATE_DELAY (12000 / FULL_SPEED)
#define STATE_2 (STATE_DELAY * 2)
#define STATE_3 (STATE_DELAY * 3)
#define STATE_4 (STATE_DELAY * 4)
#define STATE_5 (STATE_DELAY * 5)

#endif
