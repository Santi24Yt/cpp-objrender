#include "modelo.h"

void Modelo::toScreen(Matrix4 &vista, int w, int h)
{
  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    verticesCam[i] = vista.multiplyVector(verticesModelo[i]);
  }

  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    double w = verticesCam[i].w;
    verticesCam[i] = Vector4(verticesCam[i].x/w, verticesCam[i].y/w, verticesCam[i].z, verticesCam[i].w);
  }

  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    int x = (verticesCam[i].x + 1)/2 * w;
    int y = (verticesCam[i].y + 1)/2 * h;
    pair<int, int> pixel(x, y);
    pixeles[i] = pixel;
  }
}

void Modelo::restoreVertices()
{
  for (size_t i = 0; i < (*obj).vertices.size(); i++)
  {
    Puntof p = (*obj).vertices[i];
    verticesModelo[i] = Vector4(p.x, p.y, p.z, p.w);
  }
}

void Modelo::transform(Matrix4 &transform)
{
  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    verticesModelo[i] = transform.multiplyVector(verticesModelo[i]);
  }
}
