#ifndef LOADOBJ_H
#define LOADOBJ_H

#include <string>
#include <boost/tokenizer.hpp>

#include "NCCA/Vec4.h"

typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

typedef struct
{
  std::vector<Vec4> Verts;
  std::vector<Vec4> Norms;
  std::vector<Vec4> Text;
  std::vector<int> Ind;
} model;

void loadModel(const std::string &_n,
               std::vector<Vec4> &o_v,
               std::vector<Vec4> &o_vn,
               std::vector<Vec4> &o_vt,
               std::vector<int> &o_vf);

#endif
