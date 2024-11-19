#ifndef OBJREADER_H
#define OBJREADER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct pt {
  float x;
  float y;
  float z;
  float w;
};

typedef struct pt Puntof;

class Obj {
  public:
  vector<Puntof> vertices;
  vector<vector<int>> caras;
  string filedir;

  Obj(string filedir);

  void abrir();
  void cerrar();
  void leer();
  void imprimir();
  // Puntof centro();
  Puntof centroProm();
  float anchox();
  float anchoy();
  float anchoz();

  // Obj(Obj &&) = default;
  // Obj(const Obj &) = default;
  // Obj &operator=(Obj &&) = default;
  // Obj &operator=(const Obj &) = default;
  // ~Obj();

  private:
  ifstream file;

  void leerVertice(stringstream &ss, int ln);
  void leerCara(stringstream &ss, int ln);
  pair<float, float> minmaxx();
  pair<float, float> minmaxy();
  pair<float, float> minmaxz();

};

#endif
