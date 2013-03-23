/*
 * File Name : constants.h
 * Purpose : Defined constants etc
 * Creation Date : 10-02-2013
 * Last Modified : lör 23 mar 2013 21:16:14
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
#define FULL_SPEED 90

// Times
#define STATE_DELAY (2000 / FULL_SPEED * 7)
#define STATE_2 (STATE_DELAY * 2)
#define STATE_3 (STATE_DELAY * 3)
#define STATE_4 (STATE_DELAY * 4)
#define STATE_6 (STATE_DELAY * 6)

#endif
