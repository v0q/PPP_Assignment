#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <algorithm>
#include <iostream>

#include "Planet.h"

Planet::Planet()
{
  loadModel("models/p_surface.obj", p_surface.Verts, p_surface.Norms, p_surface.Text, p_surface.Ind);
  loadModel("models/p_mountains.obj", p_mountains.Verts, p_mountains.Norms, p_mountains.Text, p_mountains.Ind);
  loadModel("models/p_waters.obj", p_waters.Verts, p_waters.Norms, p_waters.Text, p_waters.Ind);
  loadModel("models/p_waterbottoms.obj", p_waterbottoms.Verts, p_waterbottoms.Norms, p_waterbottoms.Text, p_waterbottoms.Ind);

  loadModel("models/tree_trunk.obj", t_trunk.Verts, t_trunk.Norms, t_trunk.Text, t_trunk.Ind);
  loadModel("models/tree_leaves.obj", t_leaves.Verts, t_leaves.Norms, t_leaves.Text, t_leaves.Ind);

  genSurface();
  genMountains();
  genWaterbottoms();
  genWaters();
  genTree();
}

Planet::~Planet()
{
  p_surface.Verts.clear();
  std::vector<Vec4>().swap(p_surface.Verts);
  p_surface.Norms.clear();
  std::vector<Vec4>().swap(p_surface.Norms);
  p_surface.Text.clear();
  std::vector<Vec4>().swap(p_surface.Text);
  p_surface.Ind.clear();
  std::vector<int>().swap(p_surface.Ind);

  p_mountains.Verts.clear();
  std::vector<Vec4>().swap(p_mountains.Verts);
  p_mountains.Norms.clear();
  std::vector<Vec4>().swap(p_mountains.Norms);
  p_mountains.Text.clear();
  std::vector<Vec4>().swap(p_mountains.Text);
  p_mountains.Ind.clear();
  std::vector<int>().swap(p_mountains.Ind);

  p_waters.Verts.clear();
  std::vector<Vec4>().swap(p_waters.Verts);
  p_waters.Norms.clear();
  std::vector<Vec4>().swap(p_waters.Norms);
  p_waters.Text.clear();
  std::vector<Vec4>().swap(p_waters.Text);
  p_waters.Ind.clear();
  std::vector<int>().swap(p_waters.Ind);

  p_waterbottoms.Verts.clear();
  std::vector<Vec4>().swap(p_waterbottoms.Verts);
  p_waterbottoms.Norms.clear();
  std::vector<Vec4>().swap(p_waterbottoms.Norms);
  p_waterbottoms.Text.clear();
  std::vector<Vec4>().swap(p_waterbottoms.Text);
  p_waterbottoms.Ind.clear();
  std::vector<int>().swap(p_waterbottoms.Ind);
}

void Planet::draw()
{
  glCallLists(p_displayList.size(), GL_UNSIGNED_INT, &p_displayList[0]);

  for(int i = 0; i < tree_positions.size(); ++i)
  {
    glPushMatrix();
      glTranslatef(tree_positions[i].m_x, tree_positions[i].m_y, tree_positions[i].m_z);
      glCallList(t_displayList);
    glPopMatrix();
  }
}

void Planet::genSurface()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
  float min = 0.86f;
  float max = 0.92f;

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)p_surface.Ind.size(); i += 3)
      {
        // Normalizing the vertex distance to 0 -> 1 for color calculatons
        float hVal = (p_surface.Verts[p_surface.Ind[i] - 1].length() - min) / (max - min);

        if(hVal < 0.4f)
        {
          glColor3f(0.686f + 0.15f*(hVal / 0.4f), 0.592f + 0.1f*(hVal / 0.4f), 0.31f);

          // A bit of a hacky way to make sure that no duplicate positions are stored
          if(std::find(stored_positions.begin(), stored_positions.end(), p_surface.Ind[i]) == stored_positions.end())
          {
            tree_positions.push_back(Vec4(p_surface.Verts[p_surface.Ind[i] - 1]));
            stored_positions.push_back(p_surface.Ind[i]);
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
}

void Planet::genMountains()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
  float min = 0.87f;
  float max = 1.01f;

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
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
  float min = 0.78f;
  float max = 0.9f;

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
  t_displayList = glGenLists(1);
  glNewList(t_displayList, GL_COMPILE);

    glBegin(GL_TRIANGLES);
        glColor3f(0.165f, 0.106f, 0.039f);
        for(int i = 0; i < (int)t_trunk.Ind.size(); i += 3)
        {
//          Vec4 newVertex(t_trunk.Verts[t_trunk.Ind[i] - 1].m_x + tree_positions[j].m_x,
//                         t_trunk.Verts[t_trunk.Ind[i] - 1].m_y + tree_positions[j].m_y,
//                         t_trunk.Verts[t_trunk.Ind[i] - 1].m_z + tree_positions[j].m_z);
          t_trunk.Norms[t_trunk.Ind[i + 2] - 1].normalGL();
          t_trunk.Verts[t_trunk.Ind[i] - 1].vertexGL();
        }

        glColor3f(0.69f, 0.765f, 0.118f);
        for(int i = 0; i < (int)t_leaves.Ind.size(); i += 3)
        {
//          Vec4 newVertex(t_leaves.Verts[t_leaves.Ind[i] - 1].m_x + tree_positions[j].m_x,
//                         t_leaves.Verts[t_leaves.Ind[i] - 1].m_y + tree_positions[j].m_y,
//                         t_leaves.Verts[t_leaves.Ind[i] - 1].m_z + tree_positions[j].m_z);
          t_leaves.Norms[t_leaves.Ind[i + 2] - 1].normalGL();
          t_leaves.Verts[t_leaves.Ind[i] - 1].vertexGL();
        }
    glEnd();

  glEndList();
}
