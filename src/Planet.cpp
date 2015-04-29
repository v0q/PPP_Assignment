#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif
#include <iostream>
#include "Planet.h"

Planet::Planet()
{
  loadModel("models/p_surface.obj", p_surface.Verts, p_surface.Norms, p_surface.Text, p_surface.Ind);
  loadModel("models/p_mountains.obj", p_mountains.Verts, p_mountains.Norms, p_mountains.Text, p_mountains.Ind);
  loadModel("models/p_waters.obj", p_waters.Verts, p_waters.Norms, p_waters.Text, p_waters.Ind);
  loadModel("models/p_waterbottoms.obj", p_waterbottoms.Verts, p_waterbottoms.Norms, p_waterbottoms.Text, p_waterbottoms.Ind);

  genSurface();
  genMountains();
  genWaterbottoms();
  genWaters();
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
}

void Planet::genSurface()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_TRIANGLES);
      glColor3f(0.906, 0.702, 0.471);
      for(int i = 0; i < (int)p_surface.Ind.size(); i += 3)
      {
        p_surface.Norms[p_surface.Ind[i + 2] - 1].normalGL();
        p_surface.Text[p_surface.Ind[i + 1] - 1].textureGL();
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

    glBegin(GL_TRIANGLES);
      glColor3f(0.906, 0.702, 0.471);
      for(int i = 0; i < (int)p_mountains.Ind.size(); i += 3)
      {
        p_mountains.Norms[p_mountains.Ind[i + 2] - 1].normalGL();
        p_mountains.Text[p_mountains.Ind[i + 1] - 1].textureGL();
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
      glColor4f(0.114, 0.431, 0.506, 0.6);
      for(int i = 0; i < (int)p_waters.Ind.size(); i += 3)
      {
        p_waters.Norms[p_waters.Ind[i + 2] - 1].normalGL();
        p_waters.Text[p_waters.Ind[i + 1] - 1].textureGL();
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

    glBegin(GL_TRIANGLES);
      glColor3f(0.906, 0.702, 0.471);
      for(int i = 0; i < (int)p_waterbottoms.Ind.size(); i += 3)
      {
        p_waterbottoms.Norms[p_waterbottoms.Ind[i + 2] - 1].normalGL();
        p_waterbottoms.Text[p_waterbottoms.Ind[i + 1] - 1].textureGL();
        p_waterbottoms.Verts[p_waterbottoms.Ind[i] - 1].vertexGL();
      }

    glEnd();
  glEndList();
  p_displayList.push_back(id);
}

