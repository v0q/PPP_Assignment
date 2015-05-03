/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef DEFS_H
#define DEFS_H

// ---------------------------------------------------------------------------------------
/// @file Defs.h
/// @brief Some variables/macros used all around
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Re-evaluate the usage of macros
// ---------------------------------------------------------------------------------------

#include <cmath>

#define SCREENWIDTH 1680
#define SCREENHEIGHT 1050
#define WORLDRADIUS 3.0f
#define ASPHERERADIUS 1.225f
#define MOVESPEED 0.015f

const static float TWO_PI = float(2 * M_PI);
const static float PI = float(M_PI);
const static float PI2 = float(M_PI/2.0);
const static float PI4 = float(M_PI/4.0);
const static int FIRE_PARTICLES = 10;

#endif // end of DEFS_H
