#include <objreader.h>
#include <iostream>
#include <sstream>

using namespace std;

float absf(float n)
{
  if (n >= 0)
    return n;
  else
    return -n;
}

Obj::Obj(string filedir) : filedir(filedir)
{
  // this->filedir = filedir;
};

void Obj::abrir()
{
  file.open(filedir);
  if (!file.is_open())
    cerr << "No se pudo abrir el archivo " << filedir << endl;
}

void Obj::cerrar()
{
  file.close();
}

void Obj::leer()
{
  if (!file.is_open())
  {
    cerr << "No se pudo abrir el archivo " << filedir << endl;
    return;
  }

  string linea;
  int ln = 0;
  while (getline(file, linea))
  {
    stringstream ss(linea);
    string tipo;
    getline(ss, tipo, ' ');

    if (tipo == "v")
      leerVertice(ss, ln);
    else if (tipo == "f")
      leerCara(ss, ln);

    ln++;
  }
}

void Obj::leerVertice(stringstream &ss, int ln)
{
  string t;
  float pos[4];
  int i = 0;


  while (getline(ss, t, ' '))
  {
    pos[i] = stof(t);
    i++;
  }

  if (i < 3)
  {
    cerr << "Vertice mal formado en la línea " << ln << " llenando con 1.0" << endl;
  }

  for (; i < 4; i++)
  {
    pos[i] = 1.0f;
  }

  Puntof p = {pos[0], pos[1], pos[2], pos[3]};
  vertices.push_back(p);
}

void Obj::leerCara(stringstream &ss, int ln)
{
  string t;

  vector<int> indicesVertices;
  vector<int> indicesTexturas;
  vector<int> indicesNormales;

  while (getline(ss, t, ' '))
  {
    string t2;
    stringstream f(t);
    int i = 0;
    while (getline(f, t2, '/'))
    {
      if (t2 == "")
        continue;

      switch (i)
      {
        case 0:
          indicesVertices.push_back(stoi(t2));
          break;
        case 1:
          indicesTexturas.push_back(stoi(t2));
          break;
        case 2:
          indicesNormales.push_back(stoi(t2));
          break;
        default:
          break;
      }

      i = (i+1) % 3;
    }
  }

  caras.push_back(indicesVertices);
}

void Obj::imprimir()
{
  cout << "Vertices: " << vertices.size() << endl;
  for (auto p : vertices)
  {
    cout << "<" << p.x << " " << p.y << " " << p.z << " " << p.w << ">" << endl;
  }

  cout << "Caras: " << caras.size() << endl;
  for (auto fa : caras)
  {
    string f = "";
    f += "[";
    for (auto fi : fa)
    {
      f += to_string(fi);
      f += " ";
    }
    f.pop_back();
    f += "]";
    cout << f << endl;
  }
  cout << endl;
}

Puntof Obj::centroProm()
{
  float cx = 0.0f;
  float cy = 0.0f;
  float cz = 0.0f;
  float cw = 0.0f;

  for (Puntof v : vertices)
  {
    cx += v.x;
    cy += v.y;
    cz += v.z;
    cw += v.w;
  }

  float l = (float)vertices.size();

  Puntof c;
  c.x = cx/l;
  c.y = cy/l;
  c.z = cz/l;
  c.w = cw/l;

  return c;
}

pair<float, float> Obj::minmaxx()
{
  float maxx = vertices[0].x;
  float minx = vertices[0].x;

  for (Puntof v : vertices)
  {
    if (v.x > maxx)
      maxx = v.x;

    if (v.x < minx)
      minx = v.x;
  }

  return make_pair(maxx, minx);
}

 pair<float, float> Obj::minmaxy()
{
  float maxy = vertices[0].y;
  float miny = vertices[0].y;

  for (Puntof v : vertices)
  {
    if (v.y > maxy)
      maxy = v.y;

    if (v.y < miny)
      miny = v.y;
  }

  return make_pair(maxy, miny);
}

pair<float, float> Obj::minmaxz()
{
  float maxz = vertices[0].z;
  float minz = vertices[0].z;

  for (Puntof v : vertices)
  {
    if (v.z > maxz)
      maxz = v.z;

    if (v.z < minz)
      minz = v.z;
  }

  return make_pair(maxz, minz);
}

float Obj::anchox()
{
  pair<float, float> mm = minmaxx();
  return absf(mm.first - mm.second);
}

float Obj::anchoy()
{
  pair<float, float> mm = minmaxy();
  return absf(mm.first - mm.second);
}

float Obj::anchoz()
{
  pair<float, float> mm = minmaxz();
  return absf(mm.first - mm.second);
}
