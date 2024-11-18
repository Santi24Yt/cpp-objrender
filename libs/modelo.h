#ifndef MODELO_H
#define MODELO_H

#include <vector>
#include "vecmatriz.h"
#include "objreader.h"

using namespace std;

class Modelo {
  public:
  vector<Vector4> vertices;
  vector<pair<int, int>> pixeles;
  vector<vector<int>> caras;

  Modelo(Obj* objp)
  {
    this->obj = objp;
    for (Puntof p : (*objp).vertices)
    {
      verticesOG.push_back(Vector4(p.x, p.y, p.z, p.w));
    }
    vertices = verticesOG;
    pixeles.resize(verticesOG.size());
    caras = (*objp).caras;
  };

  void toScreen(Matrix4 &vista, int w, int h);
  void restoreVertices();

  private:
  Obj* obj;
  vector<Vector4> verticesOG;
};

#endif
