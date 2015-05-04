/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Initial file parsing code © by Jonathan Macey
*/

#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "LoadOBJ.h"

// ---------------------------------------------------------------------------------------
/// @file LoadOBJ.cpp
/// @brief Implementation mesh loading functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void loadModel(
               const std::string &_n,
               model &o_m
              )
{
  // Open the filestream for reading a file
  std::fstream fileIn;
  fileIn.open(_n.c_str(), std::ios::in);

  // Make sure that the file was opened
  if(!fileIn.is_open())
  {
    std::cerr << "Could not open " << _n << "\n";
    exit(EXIT_FAILURE);
  }

  // Boost parser separator
  boost::char_separator<char> sep(" /\t\r\n");

  // Read the file till we reach the end
  std::string lineBuffer;
  while(!fileIn.eof())
  {
    // Get a single line from the file and read it to the lineBuffer
    getline(fileIn, lineBuffer, '\n');
    if(lineBuffer.size() != 0)
    {
      // Using boost to parse each line using the separators defined earlier
      tokenizer tokens(lineBuffer, sep);
      tokenizer::iterator it = tokens.begin();

      // Check if we found v i.e. vertex data and store it into the vertex data
      // part of the supplied structure
      if(*it == "v")
      {
        Vec4 v(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it));
        o_m.m_Verts.push_back(v);
      }
      // Check if we found vn i.e. vertex normal data and store it into the vertex
      // normal data part of the supplied structure
      else if(*it == "vn")
      {
        Vec4 n(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it));
        o_m.m_Norms.push_back(n);
      }
      // Check if we found vt i.e. texture coordinate data and store it into the
      // texture coordinate data part of the supplied structure
      else if(*it == "vt")
      {
        Vec4 t(boost::lexical_cast<float>(*++it),
               boost::lexical_cast<float>(*++it),
               0);
        o_m.m_Text.push_back(t);
      }
      // Check if we found f i.e. triangle index data and store it into the
      // stl vector containing the indice data
      else if(*it == "f")
      {
        // First vert, textcoords & norms
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));

        // Second vert, textcoords & norms
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));

        // Third vert, textcoords & norms
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
        o_m.m_Ind.push_back(boost::lexical_cast<int>(*++it));
      }
    }
  }

  // Close the file after we've reached the eof
  fileIn.close();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void freeModelMem(
                  model &o_m
                 )
{
  // Clear the data from the vectors and swap 'em to empty ones to free up memory
  o_m.m_Verts.clear();
  std::vector<Vec4>().swap(o_m.m_Verts);
  o_m.m_Norms.clear();
  std::vector<Vec4>().swap(o_m.m_Norms);
  o_m.m_Text.clear();
  std::vector<Vec4>().swap(o_m.m_Text);
  o_m.m_Ind.clear();
  std::vector<int>().swap(o_m.m_Ind);
}
// ---------------------------------------------------------------------------------------
