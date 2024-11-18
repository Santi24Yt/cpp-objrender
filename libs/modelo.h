#ifndef MODELO_H
#define MODELO_H

#include <vector>
#include "vecmatriz.h"
#include "objreader.h"

using namespace std;

class Modelo {
  public:
  vector<Vector4> verticesCam;
  vector<pair<int, int>> pixeles;
  vector<vector<int>> caras;

  Modelo(Obj* objp)
  {
    this->obj = objp;
    for (Puntof p : (*objp).vertices)
    {
      verticesModelo.push_back(Vector4(p.x, p.y, p.z, p.w));
    }
    verticesCam = verticesModelo;
    pixeles.resize(verticesModelo.size());
    caras = (*objp).caras;
  };

  void toScreen(Matrix4 &vista, int w, int h);
  void restoreVertices();
  void transform(Matrix4 &transform);

  private:
  Obj* obj;
  vector<Vector4> verticesModelo;
};

#endif
