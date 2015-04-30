#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "LoadOBJ.h"

void loadModel(const std::string &_n, model &o_m)
{
  std::fstream fileIn;
  fileIn.open(_n.c_str(), std::ios::in);
  if(!fileIn.is_open())
  {
    std::cerr << "Could not open " << _n << "\n";
    exit(EXIT_FAILURE);
  }
  // Boost parser separator
  boost::char_separator<char> sep(" /\t\r\n");

  std::string lineBuffer;
  while(!fileIn.eof())
  {
    getline(fileIn, lineBuffer, '\n');
    if(lineBuffer.size() != 0)
    {
      tokenizer tokens(lineBuffer, sep);
      tokenizer::iterator it = tokens.begin();

      if(*it == "v")
      {
        Vec4 v(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it));
        o_m.Verts.push_back(v);
      }
      else if(*it == "vn")
      {
        Vec4 n(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it));
        o_m.Norms.push_back(n);
      }
      else if(*it == "vt")
      {
        Vec4 t(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               0);
        o_m.Text.push_back(t);
      }
      else if(*it == "f")
      {
        // First vert, textcoords & norms
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));

        // Second vert, textcoords & norms
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));

        // Third vert, textcoords & norms
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.Ind.push_back(boost::lexical_cast<int>(*++it));
      }
    }
  }

  fileIn.close();
}

void freeModelMem(model &o_m)
{
  o_m.Verts.clear();
  std::vector<Vec4>().swap(o_m.Verts);
  o_m.Norms.clear();
  std::vector<Vec4>().swap(o_m.Norms);
  o_m.Text.clear();
  std::vector<Vec4>().swap(o_m.Text);
  o_m.Ind.clear();
  std::vector<int>().swap(o_m.Ind);
}
