/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Initial code © by Jonathan Macey
*/

#ifndef LOADOBJ_H
#define LOADOBJ_H

// ---------------------------------------------------------------------------------------
/// @file LoadOBJ.h
/// @brief Structure to hold and functions to load OBJ-file data and freeing up the used
///        memory in the end.
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Nothing for now, maybe use namespaces and possibly tidy up the code. Possibly
///       turn this in to a mesh class that would have draw functions etc. For now
///       as depending on the mesh it might be handled differently the drawing will be
///       done where ever it's needed.
// ---------------------------------------------------------------------------------------

#include <string>
#include <boost/tokenizer.hpp>

#include "NCCA/Vec4.h"

typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

typedef struct
{
  // ---------------------------------------------------------------------------------------
  /// @brief stl vector containing the vertex data
  // ---------------------------------------------------------------------------------------
  std::vector<Vec4> m_Verts;

  // ---------------------------------------------------------------------------------------
  /// @brief stl vector containing the vertex normal data
  // ---------------------------------------------------------------------------------------
  std::vector<Vec4> m_Norms;

  // ---------------------------------------------------------------------------------------
  /// @brief stl vector containing the texture coordinates
  // ---------------------------------------------------------------------------------------
  std::vector<Vec4> m_Text;

  // ---------------------------------------------------------------------------------------
  /// @brief stl vector holding the vertex, vertex normal and texture coordinate
  ///        indice data of each triangle
  // ---------------------------------------------------------------------------------------
  std::vector<int> m_Ind;
} model; // end of struct

// ---------------------------------------------------------------------------------------
/// @brief Parse an OBJ-file and store the data in to the provided model structure
/// @param[in] _n Path to the OBJ-file
/// @param[out] o_m Model structure to store the data in
// ---------------------------------------------------------------------------------------
void loadModel(
               const std::string &_n,
               model &o_m
              );

// ---------------------------------------------------------------------------------------
/// @brief Function to clear the stl vectors and freeing up the memory used to store
///        the model data.
/// @param[out] o_m The structure where the data is stored in.
// ---------------------------------------------------------------------------------------
void freeModelMem(
                  model &o_m
                 );

#endif // end of LOADOBJ_H
