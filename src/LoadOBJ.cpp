#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "LoadOBJ.h"

void loadModel(const std::string &_n,
               std::vector <Vec4> &o_v,
               std::vector <Vec4> &o_vn, std::vector<Vec4> &o_vt,
               std::vector <int> &o_vf)
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
        o_v.push_back(v);
      }
      else if(*it == "vn")
      {
        Vec4 n(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it));
        o_vn.push_back(n);
      }
      else if(*it == "vt")
      {
        Vec4 t(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               0);
        o_vt.push_back(t);
      }
      else if(*it == "f")
      {
        // First vert, textcoords & norms
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));

        // Second vert, textcoords & norms
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));

        // Third vert, textcoords & norms
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        o_vf.push_back(boost::lexical_cast<int>(*++it));
      }
    }
  }

  fileIn.close();
}
