#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "LoadOBJ.h"

void loadModel(const std::string &_n,
               std::vector <Vec4> &o_v,
               std::vector <Vec4> &o_vn,
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
        n.normalize();
        o_vn.push_back(n);
      }
      else if(*it == "f")
      {
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        ++(++it);
        o_vf.push_back(boost::lexical_cast<int>(*++it));
        ++(++it);
        o_vf.push_back(boost::lexical_cast<int>(*++it));
      }
    }
  }

  fileIn.close();
}
