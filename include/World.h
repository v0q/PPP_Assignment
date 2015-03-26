#ifndef WORLD_H__
#define WORLD_H__

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <OpenGL/gl.h>

#include "Asteroids.h"
#include "LoadOBJ.h"
#include "NCCA/Vec4.h"

#define SKYBOXRADIUS 15

class World
{
  public:
    World() : max_asteroids(500) { loadModel("models/sphere.obj", skybox_Verts, skybox_Norms, skybox_Text, skybox_Ind);
                                   loadModel("models/planet.obj", planet_Verts, planet_Norms, planet_Text, planet_Ind);
                                   planet(); atmosphere(); skybox(); }
    ~World();
    void initStars(int _a);
    void drawStars(Vec4 _c) const;
    void drawWorld();
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _ndir) const;

    std::vector<Asteroid> asteroids;
    std::list<int> a_ColIndices;

  private:
    void planet();
    void atmosphere();
    void skybox();
    void generate_Asteroids();
    void tSphere(int _d, int _ndir) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _ndir) const;
    void partByDist();

    // Skybox model
    std::vector<Vec4> skybox_Verts;
    std::vector<Vec4> skybox_Norms;
    std::vector<Vec4> skybox_Text;
    std::vector<int> skybox_Ind;

    // Planet model
    std::vector<Vec4> planet_Verts;
    std::vector<Vec4> planet_Norms;
    std::vector<Vec4> planet_Text;
    std::vector<int> planet_Ind;

    std::vector<Vec4> stars;
    std::vector<GLuint> w_displayList;
    int max_asteroids;

    GLuint skyBoxTexId;
};

#endif
