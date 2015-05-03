/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

// ---------------------------------------------------------------------------------------
/// @file Icosahedron.h
/// @brief Header file holding the vector data for icosahedron and octahedron shapes
///        both of which can be used for the atmosphere by passing either one to
///        the subdivision function in World.cpp. This way we achieve a geodesic dome
///        for the atmosphere.
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidy up the shape definitions
// ---------------------------------------------------------------------------------------

#include "NCCA/Vec4.h"

// ---------------------------------------------------------------------------------------
/// @brief Hard calculated constants that are used for as vertex coordinates
// ---------------------------------------------------------------------------------------
float c = 0.525731;
float s = 0.850651;

// ---------------------------------------------------------------------------------------
/// @brief Triangle data for the icosahedron shape
// ---------------------------------------------------------------------------------------
Vec4 icosHedron[20][3] = {
  // T1
  {Vec4(s, 0.0f, c),
  Vec4(s, 0.0f, -c),
  Vec4(c, s, 0.0f)},
  // T2
  {Vec4(s, 0.0f, c),
  Vec4(c, -s, 0.0f),
  Vec4(s, 0.0f, -c)},
  // T3
  {Vec4(-s, 0.0f, -c),
  Vec4(-s, 0, c),
  Vec4(-c, s, 0.0f)},
  // T4
  {Vec4(-s, 0.0f, c),
  Vec4(-s, 0.0f, -c),
  Vec4(-c, -s, 0.0f)},
  // T4
  {Vec4(c, s, 0.0f),
  Vec4(-c, s, 0.0f),
  Vec4(0, c, s)},
  // T5
  {Vec4(-c, s, 0.0f),
  Vec4(c, s, 0.0f),
  Vec4(0.0f, c, -s)},
  // T6
  {Vec4(0.0f, -c, -s),
  Vec4(0.0f, c, -s),
  Vec4(s, 0.0f, -c)},
  // T7
  {Vec4(0.0f, c, -s),
  Vec4(0.0f, -c, -s),
  Vec4(-s, 0.0f, -c)},
  // T8
  {Vec4(c, -s, 0.0f),
  Vec4(-c, -s, 0.0f),
  Vec4(0.0f, -c, -s)},
  // T9
  {Vec4(-c, -s, 0.0f),
  Vec4(c, -s, 0.0f),
  Vec4(0.0f, -c, s)},
  // T10
  {Vec4(0.0f, c, s),
  Vec4(0.0f, -c, s),
  Vec4(s, 0.0f, c)},
  // T11
  {Vec4(0.0f, -c, s),
  Vec4(0.0f, c, s),
  Vec4(-s, 0.0f, c)},
  // T12
  {Vec4(c, s, 0.0f),
  Vec4(s, 0.0f, -c),
  Vec4(0.0f, c, -s)},
  // T13
  {Vec4(s, 0.0f, c),
  Vec4(c, s, 0.0f),
  Vec4(0.0f, c, s)},
  // T14
  {Vec4(-s, 0.0f, -c),
  Vec4(-c, s, 0.0f),
  Vec4(0.0f, c, -s)},
  // T15
  {Vec4(-c, s, 0.0f),
  Vec4(-s, 0.0f, c),
  Vec4(0.0f, c, s)},
  // T16
  {Vec4(s, 0.0f, -c),
  Vec4(c, -s, 0.0f),
  Vec4(0.0f, -c, -s)},
  // T17
  {Vec4(c, -s, 0.0f),
  Vec4(s, 0.0f, c),
  Vec4(0.0f, -c, s)},
  // T18
  {Vec4(-s, 0.0f, -c),
  Vec4(0.0f, -c, -s),
  Vec4(-c, -s, 0.0f)},
  // T19
  {Vec4(-s, 0.0f, c),
  Vec4(-c, -s, 0.0f),
  Vec4(0.0f, -c, s)}
}; // end of icosahedron triangle data

// ---------------------------------------------------------------------------------------
/// @brief Vertex coordinate element for octahedron
// ---------------------------------------------------------------------------------------
float cOcta = 1.0f;

// ---------------------------------------------------------------------------------------
/// @brief Triangle data for the octahedron shape
// ---------------------------------------------------------------------------------------
Vec4 octaHedron[8][3] = {
  // T1
  {Vec4(0.0f, cOcta, 0.0f),
  Vec4(-cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, cOcta)},
  // T2
  {Vec4(0.0f, cOcta, 0.0f),
  Vec4(cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, cOcta)},
  // T3
  {Vec4(0.0f, cOcta, 0.0f),
  Vec4(-cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, -cOcta)},
  // T4
  {Vec4(0.0f, cOcta, 0.0f),
  Vec4(cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, -cOcta)},
  // T5
  {Vec4(0.0f, -cOcta, 0.0f),
  Vec4(-cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, cOcta)},
  // T6
  {Vec4(0.0f, -cOcta, 0.0f),
  Vec4(cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, cOcta)},
  // T7
  {Vec4(0.0f, -cOcta, 0.0f),
  Vec4(-cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, -cOcta)},
  // T8
  {Vec4(0.0f, -cOcta, 0.0f),
  Vec4(cOcta, 0.0f, 0.0f),
  Vec4(0.0f, 0.0f, -cOcta)}
}; // end of octahedron triangle data

#endif // end of ICOSAHEDRON_H
