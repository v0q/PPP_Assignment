#include <cmath>
#include <iostream>

#include "Defs.h"
#include "Universe.h"

void Universe::arcBallVector(int _x, int _y, float *v)
{
  float d, a;

  v[0] = _x;
  v[1] = _y;
  d = sqrt(v[0] * v[0] + v[1] * v[1]);
  v[2] = cos(TWO_PI * ((d < 1.0) ? d : 1.0));
  a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  std::cout << a << "\n";
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
}
