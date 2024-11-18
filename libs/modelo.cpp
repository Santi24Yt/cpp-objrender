#include "modelo.h"

void Modelo::toScreen(Matrix4 &vista, int w, int h)
{
  for (long unsigned int i = 0; i < vertices.size(); i++) {
    vertices[i] = vista.multiplyVector(verticesOG[i]);
  }

  for (long unsigned int i = 0; i < vertices.size(); i++) {
    double w = vertices[i].w;
    vertices[i] = Vector4(vertices[i].x/w, vertices[i].y/w, vertices[i].z, vertices[i].w);
  }

  for (long unsigned int i = 0; i < vertices.size(); i++) {
    int x = (vertices[i].x + 1)/2 * w;
    int y = (vertices[i].y + 1)/2 * h;
    pair<int, int> pixel(x, y);
    pixeles[i] = pixel;
  }
}

void Modelo::restoreVertices()
{
  for (long unsigned int i = 0; i < (*obj).vertices.size(); i++)
  {
    Puntof p = (*obj).vertices[i];
    verticesOG[i] = Vector4(p.x, p.y, p.z, p.w);
  }
}
