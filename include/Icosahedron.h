#ifndef ICOSAHEDRON_H__
#define ICOSAHEDRON_H__

#include "NCCA/Vec4.h"

float c = 0.525731;
float s = 0.850651;

Vec4 icosHedron[20][3] = {

{Vec4(s, 0.0, c),
Vec4(s, 0.0, -c),
Vec4(c, s, 0.0)},

{Vec4(s, 0.0, c),
Vec4(c, -s, 0.0),
Vec4(s, 0.0, -c)},

{Vec4(-s, 0.0, -c),
Vec4(-s, 0, c),
Vec4(-c, s, 0.0)},

{Vec4(-s, 0.0, c),
Vec4(-s, 0.0, -c),
Vec4(-c, -s, 0.0)},

{Vec4(c, s, 0.0),
Vec4(-c, s, 0.0),
Vec4(0, c, s)},

{Vec4(-c, s, 0.0),
Vec4(c, s, 0.0),
Vec4(0.0, c, -s)},

{Vec4(0.0, -c, -s),
Vec4(0.0, c, -s),
Vec4(s, 0.0, -c)},

{Vec4(0.0, c, -s),
Vec4(0.0, -c, -s),
Vec4(-s, 0.0, -c)},

{Vec4(c, -s, 0.0),
Vec4(-c, -s, 0.0),
Vec4(0.0, -c, -s)},

{Vec4(-c, -s, 0.0),
Vec4(c, -s, 0.0),
Vec4(0.0, -c, s)},

{Vec4(0.0, c, s),
Vec4(0.0, -c, s),
Vec4(s, 0.0, c)},

{Vec4(0.0, -c, s),
Vec4(0.0, c, s),
Vec4(-s, 0.0, c)},

{Vec4(c, s, 0.0),
Vec4(s, 0.0, -c),
Vec4(0.0, c, -s)},

{Vec4(s, 0.0, c),
Vec4(c, s, 0.0),
Vec4(0.0, c, s)},

{Vec4(-s, 0.0, -c),
Vec4(-c, s, 0.0),
Vec4(0.0, c, -s)},

{Vec4(-c, s, 0.0),
Vec4(-s, 0.0, c),
Vec4(0.0, c, s)},

{Vec4(s, 0.0, -c),
Vec4(c, -s, 0.0),
Vec4(0.0, -c, -s)},

{Vec4(c, -s, 0.0),
Vec4(s, 0.0, c),
Vec4(0.0, -c, s)},

{Vec4(-s, 0.0, -c),
Vec4(0.0, -c, -s),
Vec4(-c, -s, 0.0)},

{Vec4(-s, 0.0, c),
Vec4(-c, -s, 0.0),
Vec4(0.0, -c, s)}

};

float cOcta = 1.0f;

Vec4 octaHedron[8][3] = {

// F1
{Vec4(0.0f, cOcta, 0.0f),
Vec4(-cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, cOcta)},
// F2
{Vec4(0.0f, cOcta, 0.0f),
Vec4(cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, cOcta)},
// F3
{Vec4(0.0f, cOcta, 0.0f),
Vec4(-cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, -cOcta)},
// F4
{Vec4(0.0f, cOcta, 0.0f),
Vec4(cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, -cOcta)},
// F5
{Vec4(0.0f, -cOcta, 0.0f),
Vec4(-cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, cOcta)},
// F6
{Vec4(0.0f, -cOcta, 0.0f),
Vec4(cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, cOcta)},
// F7
{Vec4(0.0f, -cOcta, 0.0f),
Vec4(-cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, -cOcta)},
// F8
{Vec4(0.0f, -cOcta, 0.0f),
Vec4(cOcta, 0.0f, 0.0f),
Vec4(0.0f, 0.0f, -cOcta)}

};

#endif
