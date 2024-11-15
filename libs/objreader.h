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

  Obj(string filedir);

  void abrir();
  void cerrar();
  void leer();
  void imprimir();

  // Obj(Obj &&) = default;
  // Obj(const Obj &) = default;
  // Obj &operator=(Obj &&) = default;
  // Obj &operator=(const Obj &) = default;
  // ~Obj();

  private:
  string filedir;
  ifstream file;

  void leerVertice(stringstream &ss, int ln);
  void leerCara(stringstream &ss, int ln);

};

#endif
