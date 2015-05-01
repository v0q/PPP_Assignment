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

  boost::random::uniform_int_distribution<> u_random(25, 250);
  max_clouds = u_random(rng);

  loadModel("models/p_surface.obj", p_surface);
  loadModel("models/p_mountains.obj", p_mountains);
  loadModel("models/p_waters.obj", p_waters);
  loadModel("models/p_waterbottoms.obj", p_waterbottoms);
  loadModel("models/tree_trunk.obj", t_trunk);
  loadModel("models/tree_leaves.obj", t_leaves);
  loadModel("models/cloud_1.obj", m_cloud);

  loadTexture("textures/cloud_particle.png", c_texture);

  genSurface();
  genMountains();
  genWaterbottoms();
  genWaters();
  genTree();
  genClouds();
}

Planet::~Planet()
{
  freeModelMem(p_surface);
  freeModelMem(p_mountains);
  freeModelMem(p_waters);
  freeModelMem(p_waterbottoms);
  freeModelMem(t_trunk);
  freeModelMem(t_leaves);

  tree_positions.clear();
  std::vector<Vec4>().swap(tree_positions);
  clouds.clear();
  std::vector<cloud>().swap(clouds);
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
      glRotatef(clouds[i].rot += 0.1f, clouds[i].rAxis.m_x, clouds[i].rAxis.m_y, clouds[i].rAxis.m_z);
      glTranslatef(0.0f, 1.0f, 0.0f);
      glScalef(clouds[i].scale, clouds[i].scale, clouds[i].scale);
      glCallList(c_displayList[0]);
    glPopMatrix();
  }
}

void Planet::genSurface()
{
  float min = 0.86f;
  float max = 0.92f;
  bool *stored_position = new bool[(int)p_surface.Verts.size()];

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)p_surface.Ind.size(); i += 3)
      {
        // Normalizing the vertex distance to 0 -> 1 for color calculatons
        float hVal = (p_surface.Verts[p_surface.Ind[i] - 1].length() - min) / (max - min);

        if(hVal < 0.4f)
        {
          glColor3f(0.686f + 0.15f*(hVal / 0.4f), 0.592f + 0.1f*(hVal / 0.4f), 0.31f);

          if(stored_position[p_surface.Ind[i] - 1] == false)
          {
            tree_positions.push_back(Vec4(p_surface.Verts[p_surface.Ind[i] - 1]));
            stored_position[p_surface.Ind[i] - 1] = true;
          }
        }
        else
          glColor3f(0.471f, 0.565f + 0.35f*(hVal - 0.49f) / 0.4f, 0.188f);

        p_surface.Norms[p_surface.Ind[i + 2] - 1].normalGL();
        p_surface.Verts[p_surface.Ind[i] - 1].vertexGL();
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
      for(int i = 0; i < (int)p_mountains.Ind.size(); i += 3)
      {
        float hVal = (p_mountains.Verts[p_mountains.Ind[i] - 1].length() - min) / (max - min);

        if(hVal > 0.7f)
          glColor3f(0.357f, 0.329f, 0.267f);
        else
          glColor3f(0.31f - 0.1 * (hVal / 0.7f), 0.286f - 0.1 * (hVal / 0.7f), 0.235f - 0.1 * (hVal / 0.7f));
        p_mountains.Norms[p_mountains.Ind[i + 2] - 1].normalGL();
        p_mountains.Verts[p_mountains.Ind[i] - 1].vertexGL();
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
      for(int i = 0; i < (int)p_waters.Ind.size(); i += 3)
      {
        p_waters.Norms[p_waters.Ind[i + 2] - 1].normalGL();
        p_waters.Verts[p_waters.Ind[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);
}

void Planet::genWaterbottoms()
{
  float min = 0.78f;
  float max = 0.9f;

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)p_waterbottoms.Ind.size(); i += 3)
      {
        float hVal = (p_waterbottoms.Verts[p_waterbottoms.Ind[i] - 1].length() - min) / (max - min);

        if(hVal < 0.7f)
          glColor3f(0.60f, 0.698f, 0.729f);
        else
          glColor3f(0.686f + 0.15f*(hVal / 0.7f), 0.592f + 0.1f*(hVal / 0.7f), 0.31f);

        p_waterbottoms.Norms[p_waterbottoms.Ind[i + 2] - 1].normalGL();
        p_waterbottoms.Verts[p_waterbottoms.Ind[i] - 1].vertexGL();
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
      for(int i = 0; i < (int)t_trunk.Ind.size(); i += 3)
      {
        t_trunk.Norms[t_trunk.Ind[i + 2] - 1].normalGL();
        t_trunk.Verts[t_trunk.Ind[i] - 1].vertexGL();
      }
    glEnd();

  glEndList();

  t_displayList.push_back(id);

  id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)t_leaves.Ind.size(); i += 3)
      {
        t_leaves.Norms[t_leaves.Ind[i + 2] - 1].normalGL();
        t_leaves.Verts[t_leaves.Ind[i] - 1].vertexGL();
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
      for(int i = 0; i < (int)m_cloud.Ind.size(); i += 3)
      {
        m_cloud.Norms[m_cloud.Ind[i + 2] - 1].normalGL();
        m_cloud.Verts[m_cloud.Ind[i] - 1].vertexGL();
      }
    glEnd();

  glEndList();

  c_displayList.push_back(id);

  boost::random::uniform_int_distribution<> u_random(1, 100);

  for(int i = 0; i < max_clouds; ++i)
  {
    cloud aCloud;
    aCloud.rAxis = Vec4(u_random(rng)/100.0f * 2.0f - 1.0f,
                        u_random(rng)/100.0f * 2.0f - 1.0f,
                        u_random(rng)/100.0f * 2.0f - 1.0f);
    aCloud.rAxis.normalize();

    aCloud.rot = u_random(rng)*3.6f;
    aCloud.scale = u_random(rng) / (100.0f * 20.0f) + 0.01f;

    clouds.push_back(aCloud);
  }
}
