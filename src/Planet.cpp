/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <algorithm>
#include <cmath>
#include <ctime>

#include "Planet.h"
#include "TextureOBJ.h"
#include "NCCA/GLFunctions.h"

// ---------------------------------------------------------------------------------------
Planet::Planet()
{
  rng.seed(time(NULL));

  // Use the boost's rng to have a different amount of clouds each play time the
  // game is played
  boost::random::uniform_int_distribution<> u_random(25, 125);
  max_clouds = u_random(rng);

  // Load the planet related models to their respective structures
  loadModel("models/p_surface.obj", m_pSurface);
  loadModel("models/p_mountains.obj", m_pMountains);
  loadModel("models/p_waters.obj", m_pWaters);
  loadModel("models/p_waterbottoms.obj", m_pSeabeds);
  loadModel("models/tree_trunk.obj", m_tTrunk);
  loadModel("models/tree_leaves.obj", m_tLeaves);
  loadModel("models/cloud_1.obj", m_cloudGeometry);

  // Call all the functions that generate the displaylists, calculate vertex colors etc.
  genSurface();
  genMountains();
  genSeabeds();
  genWaters();
  genTree();
  genClouds();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
Planet::~Planet()
{
  // Free up all the memory reserved for the model structures
  freeModelMem(m_pSurface);
  freeModelMem(m_pMountains);
  freeModelMem(m_pWaters);
  freeModelMem(m_pSeabeds);
  freeModelMem(m_tTrunk);
  freeModelMem(m_tLeaves);

  // Clear the tree and cloud vectors and free up the space
  tree_positions.clear();
  std::vector<Vec4>().swap(tree_positions);
  clouds.clear();
  std::vector<m_cloud>().swap(clouds);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::draw()
{
  // Call the displaylists of the planet surface, mountains, water surface and seabeds
  glCallLists(p_displayList.size(), GL_UNSIGNED_INT, &p_displayList[0]);

  // Loop through the trees, orient them and translate them to their respective positions
  for(int i = 0; i < (int)tree_positions.size(); ++i)
  {
    // Calculating the rotation axis of a tree by calculating the cross product of
    // the desired position and vector(0, 1, 0)
    Vec4 vecTo = tree_positions[i];
    Vec4 rotAxis = Vec4(0, 1, 0).cross(vecTo);

    // Normalising both vectors
    vecTo.normalize();
    rotAxis.normalize();

    // Calculating the rotation angle by taking the arccos of the dot product of
    // the desired position and vector(0, 1, 0).
    float theta = acosf(vecTo.dot(Vec4(0, 1, 0))) * 180/M_PI;

    glPushMatrix();

      // Rotating the tree based on the previously calculated angle and rotation axis and
      // translating it to the desired position. The rotation orients the tree properly
      glTranslatef(tree_positions[i].m_x, tree_positions[i].m_y, tree_positions[i].m_z);
      glRotatef(theta, rotAxis.m_x, rotAxis.m_y, rotAxis.m_z);

      // Call the list that holds the tree trunk data
      glCallList(t_displayList[0]);

      // Give every other tree a different leaf color
      if(!(i%2))
        glColor3f(0.706f, 0.706f, 0.251f);
      else
        glColor3f(0.349f, 0.584f, 0.196f);

      glCallList(t_displayList[1]);

    glPopMatrix();
  }

  // Looping through the clouds, rotating each one slowly and scaling 'em to their respective sizes.
  for(int i = 0; i < max_clouds; ++i)
  {
    glPushMatrix();
      glRotatef(clouds[i].m_rot += 0.1f, clouds[i].m_rAxis.m_x, clouds[i].m_rAxis.m_y, clouds[i].m_rAxis.m_z);
      glTranslatef(0.0f, 1.0f, 0.0f);
      glScalef(clouds[i].m_scale, clouds[i].m_scale, clouds[i].m_scale);
      glCallList(c_displayList[0]);
    glPopMatrix();
  }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genSurface()
{
  // Approximated min and max vertex length to be used for the height based color calculatiosn
  float min = 0.86f;
  float max = 0.92f;

  // Making an array holding boolean data on whether a tree is already placed on a certain vertex
  bool *stored_position = new bool[(int)m_pSurface.m_Verts.size()];

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pSurface.m_Ind.size(); i += 9)
      {
        // Arrays to hold the color values for each vertex of a triangle
        float r[3];
        float g[3];
        float b[3];
        int j = 0;

        for(int k = i; k < i + 9; k += 3)
        {
          // Normalizing the vertex distance to 0 -> 1 for color calculations
          float hVal = (m_pSurface.m_Verts[m_pSurface.m_Ind[k] - 1].length() - min) / (max - min);

          if(hVal < 0.4f)
          {
            r[j] = 0.686f + 0.15f*(hVal / 0.4f);
            g[j] = 0.592f + 0.1f*(hVal / 0.4f);
            b[j] = 0.31f;

            if(stored_position[m_pSurface.m_Ind[k] - 1] == false)
            {
              tree_positions.push_back(Vec4(m_pSurface.m_Verts[m_pSurface.m_Ind[k] - 1]));
              stored_position[m_pSurface.m_Ind[k] - 1] = true;
            }
          }
          else
          {
            r[j] = 0.471f;
            g[j] = 0.565f + 0.35f*(hVal - 0.49f) / 0.4f;
            b[j] = 0.188f;
          }
          ++j;
        }

        // Only using the normals of the first vertex in each triangle to achieve
        // flat shading
        m_pSurface.m_Norms[m_pSurface.m_Ind[i + 2] - 1].normalGL();
        glColor3f(r[0], g[0], b[0]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i] - 1].vertexGL();

        //glColor3f(r[1], g[1], b[1]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i + 3] - 1].vertexGL();

        //glColor3f(r[2], g[2], b[2]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i + 6] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);

  // Freeing up the memory allocated for the boolean array
  delete [] stored_position;
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genMountains()
{
  // Approximated min and max vertex length to be used for the height based color calculatiosn
  float min = 0.87f;
  float max = 1.01f;

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pMountains.m_Ind.size(); i += 3)
      {
        // Normalizing the vertex distance to 0 -> 1 for color calculations
        float hVal = (m_pMountains.m_Verts[m_pMountains.m_Ind[i] - 1].length() - min) / (max - min);

        // Based on the distance of a vertex we're coloring it differently
        if(hVal > 0.7f)
          glColor3f(0.357f, 0.329f, 0.267f);
        else
          glColor3f(0.31f - 0.1 * (hVal / 0.7f), 0.286f - 0.1 * (hVal / 0.7f), 0.235f - 0.1 * (hVal / 0.7f));
        m_pMountains.m_Norms[m_pMountains.m_Ind[i + 2] - 1].normalGL();
        m_pMountains.m_Verts[m_pMountains.m_Ind[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genWaters()
{
  // Loads the water surface model data into a displaylist
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      glColor4f(0.671f, 0.827f, 0.878f, 0.6);
      for(int i = 0; i < (int)m_pWaters.m_Ind.size(); i += 3)
      {
        m_pWaters.m_Norms[m_pWaters.m_Ind[i + 2] - 1].normalGL();
        m_pWaters.m_Verts[m_pWaters.m_Ind[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genSeabeds()
{
  // Approximated min and max vertex length to be used for the height based color calculatiosn
  float min = 0.78f;
  float max = 0.9f;

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pSeabeds.m_Ind.size(); i += 3)
      {
        // Normalizing the vertex distance to 0 -> 1 for color calculations
        float hVal = (m_pSeabeds.m_Verts[m_pSeabeds.m_Ind[i] - 1].length() - min) / (max - min);

        // Based on the distance of a vertex we're coloring it differently
        if(hVal < 0.7f)
          glColor3f(0.60f, 0.698f, 0.729f);
        else
          glColor3f(0.686f + 0.15f*(hVal / 0.7f), 0.592f + 0.1f*(hVal / 0.7f), 0.31f);

        m_pSeabeds.m_Norms[m_pSeabeds.m_Ind[i + 2] - 1].normalGL();
        m_pSeabeds.m_Verts[m_pSeabeds.m_Ind[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genTree()
{
  // Load the trunk data to a displaylist
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      glColor3f(0.165f, 0.106f, 0.039f);
      for(int i = 0; i < (int)m_tTrunk.m_Ind.size(); i += 3)
      {
        m_tTrunk.m_Norms[m_tTrunk.m_Ind[i + 2] - 1].normalGL();
        m_tTrunk.m_Verts[m_tTrunk.m_Ind[i] - 1].vertexGL();
      }
    glEnd();

  glEndList();

  t_displayList.push_back(id);

  // Load the leaf data to a separate displaylist so we're able to change the color
  // of just the leaves later
  id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_tLeaves.m_Ind.size(); i += 3)
      {
        m_tLeaves.m_Norms[m_tLeaves.m_Ind[i + 2] - 1].normalGL();
        m_tLeaves.m_Verts[m_tLeaves.m_Ind[i] - 1].vertexGL();
      }
    glEnd();

  glEndList();

  t_displayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Planet::genClouds()
{
  // Loads the cloud model into a displaylist
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      glColor3f(1, 1, 1);
      for(int i = 0; i < (int)m_cloudGeometry.m_Ind.size(); i += 3)
      {
        m_cloudGeometry.m_Norms[m_cloudGeometry.m_Ind[i + 2] - 1].normalGL();
        m_cloudGeometry.m_Verts[m_cloudGeometry.m_Ind[i] - 1].vertexGL();
      }
    glEnd();

  glEndList();

  c_displayList.push_back(id);

  boost::random::uniform_int_distribution<> u_random(1, 100);

  // Randomise the rotation axis, rotation and scale for each cloud
  for(int i = 0; i < max_clouds; ++i)
  {
    m_cloud aCloud;
    aCloud.m_rAxis = Vec4(u_random(rng)/100.0f * 2.0f - 1.0f,
                        u_random(rng)/100.0f * 2.0f - 1.0f,
                        u_random(rng)/100.0f * 2.0f - 1.0f);
    aCloud.m_rAxis.normalize();

    aCloud.m_rot = u_random(rng)*3.6f;
    aCloud.m_scale = u_random(rng) / (100.0f * 20.0f) + 0.01f;

    clouds.push_back(aCloud);
  }
}
// ---------------------------------------------------------------------------------------
