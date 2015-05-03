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

Planet::Planet()
{
  rng.seed(time(NULL));

  boost::random::uniform_int_distribution<> u_random(25, 125);
  max_clouds = u_random(rng);

  loadModel("models/p_surface.obj", m_pSurface);
  loadModel("models/p_mountains.obj", m_pMountains);
  loadModel("models/p_waters.obj", m_pWaters);
  loadModel("models/p_waterbottoms.obj", m_pSeabeds);
  loadModel("models/tree_trunk.obj", m_tTrunk);
  loadModel("models/tree_leaves.obj", m_tLeaves);
  loadModel("models/cloud_1.obj", m_cloudGeometry);

  genSurface();
  genMountains();
  genSeabeds();
  genWaters();
  genTree();
  genClouds();
}

Planet::~Planet()
{
  freeModelMem(m_pSurface);
  freeModelMem(m_pMountains);
  freeModelMem(m_pWaters);
  freeModelMem(m_pSeabeds);
  freeModelMem(m_tTrunk);
  freeModelMem(m_tLeaves);

  tree_positions.clear();
  std::vector<Vec4>().swap(tree_positions);
  clouds.clear();
  std::vector<m_cloud>().swap(clouds);
}

void Planet::draw()
{
  glCallLists(p_displayList.size(), GL_UNSIGNED_INT, &p_displayList[0]);

  for(int i = 0; i < (int)tree_positions.size(); ++i)
  {
    // Calculating the rotation axis
    Vec4 vecTo = tree_positions[i];
    Vec4 rotAxis = Vec4(0, 1, 0).cross(vecTo);

    vecTo.normalize();
    rotAxis.normalize();

    // Rotation angle
    float theta = acosf(vecTo.dot(Vec4(0, 1, 0))) * 180/M_PI;

    glPushMatrix();

      glTranslatef(tree_positions[i].m_x, tree_positions[i].m_y, tree_positions[i].m_z);
      glRotatef(theta, rotAxis.m_x, rotAxis.m_y, rotAxis.m_z);

      glCallList(t_displayList[0]);

      if(!(i%2))
        glColor3f(0.706f, 0.706f, 0.251f);
      else
        glColor3f(0.349f, 0.584f, 0.196f);

      glCallList(t_displayList[1]);

    glPopMatrix();
  }

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

void Planet::genSurface()
{
  float min = 0.86f;
  float max = 0.92f;
  bool *stored_position = new bool[(int)m_pSurface.m_Verts.size()];

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pSurface.m_Ind.size(); i += 9)
      {
        float r[3];
        float g[3];
        float b[3];
        int j = 0;
        // Normalizing the vertex distance to 0 -> 1 for color calculatons
        for(int k = i; k < i + 9; k += 3)
        {
          float hVal = (m_pSurface.m_Verts[m_pSurface.m_Ind[k] - 1].length() - min) / (max - min);

          if(hVal < 0.4f)
          {
            //glColor3f(0.686f + 0.15f*(hVal / 0.4f), 0.592f + 0.1f*(hVal / 0.4f), 0.31f);
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
          //glColor3f(0.471f, 0.565f + 0.35f*(hVal - 0.49f) / 0.4f, 0.188f);
            r[j] = 0.471f;
            g[j] = 0.565f + 0.35f*(hVal - 0.49f) / 0.4f;
            b[j] = 0.188f;
          }
          ++j;
        }

        m_pSurface.m_Norms[m_pSurface.m_Ind[i + 2] - 1].normalGL();
        glColor3f(r[0], g[0], b[0]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i] - 1].vertexGL();

        glColor3f(r[1], g[1], b[1]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i + 3] - 1].vertexGL();

        glColor3f(r[2], g[2], b[2]);
        m_pSurface.m_Verts[m_pSurface.m_Ind[i + 6] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);

  delete [] stored_position;
}

void Planet::genMountains()
{
  float min = 0.87f;
  float max = 1.01f;

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pMountains.m_Ind.size(); i += 3)
      {
        float hVal = (m_pMountains.m_Verts[m_pMountains.m_Ind[i] - 1].length() - min) / (max - min);

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

void Planet::genWaters()
{
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

void Planet::genSeabeds()
{
  float min = 0.78f;
  float max = 0.9f;

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_pSeabeds.m_Ind.size(); i += 3)
      {
        float hVal = (m_pSeabeds.m_Verts[m_pSeabeds.m_Ind[i] - 1].length() - min) / (max - min);

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

void Planet::genTree()
{
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

void Planet::genClouds()
{
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
