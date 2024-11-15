#include <iostream>
#include <string>
#include <imagen.h>
#include <objreader.h>

int main (int argc, char *argv[])
{
  std::string archivo;
  if (argc < 2)
  {
    std::cout << "Introduce nombre de archivo: ";
    std::cin >> archivo;
  } else {
    archivo = argv[1];
  }

  Obj cuboTri("Cube_Triangles.obj");

  cuboTri.abrir();
  cuboTri.leer();

  cuboTri.imprimir();
  
  cuboTri.cerrar();

  return 0;
}
