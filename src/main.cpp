#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "objreader.h"
#include "imagen.h"
#include "vecmatriz.h"
#include "modelo.h"

Matrix4 gentransf(Matrix4 &rot, Matrix4 &trans, Matrix4 &scale) {
  return Matrix4::multiply(Matrix4::multiply(rot, trans), scale);
}

int main (int argc, char *argv[])
{
  std::string archivo;
  int optimize = 0;
  if (argc < 2)
  {
    std::cout << "Introduce nombre de archivo: ";
    std::cin >> archivo;
  } else {
    archivo = argv[1];
    if (argc >= 3)
      optimize = stoi(argv[2]);
  }

  Obj objf(archivo);

  objf.abrir();
  objf.leer();
  // objf.imprimir();
  objf.cerrar();

  cout << "Modelo: " << archivo << endl;
  cout << "No. de vértices: " << objf.vertices.size() << endl;
  cout << "No. de caras: " << objf.caras.size() << endl;

  Imagen<1000, 800> img1; 

  Vector4 ejes[3][2] = {
    { Vector4(0,0,0,1), Vector4(1,0,0,1) },
    { Vector4(0,0,0,1), Vector4(0,1,0,1) },
    { Vector4(0,0,0,1), Vector4(0,0,1,1) }
  };


  Puntof centroCuboPf = objf.centroProm();
  Vector3 centroCubo(centroCuboPf.x, centroCuboPf.y, centroCuboPf.z);

  Vector3 cam(centroCuboPf.x + objf.anchox() + 10, 2, 0);

  Matrix4 look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
  Matrix4 persp = Matrix4::perspective(60, (float)img1.width/img1.height, 0, 100);
  // Matrix4 orth = Matrix4::orthographic(2, -2, -2, 2, -2, 2);

  int rotspeedy = 2;
  int rotspeedx = 0;
  int rotspeedz = 0;
  double scalex = 1.0;
  double scaley = 1.0;
  double scalez = 1.0;
  double speedx = 0.0;
  double speedy = 0.0;
  double speedz = 0.0;

  Matrix4 rot = Matrix4::rotateY((M_PI*(0.2*rotspeedy))/144);
  Matrix4 trans = Matrix4();
  Matrix4 scale = Matrix4();
  
  Matrix4 transf = gentransf(rot, trans, scale);
  Matrix4 vista = Matrix4::multiply(look, persp);

  Vector4 ejesimg[3][2];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ejesimg[i][j] = ejes[i][j];
    }
  }

  Modelo modelo1(&objf);

  unsigned int colors[12] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF,
                             0x00FFFFFF, 0xFF00FFFF, 0xFFFFFFFF, 0xF0A000FF,
                             0x00F0A0FF, 0xF000A0FF, 0xF0A0F0FF, 0xADC034FF};



  sf::RenderWindow window(sf::VideoMode(img1.width, img1.height), "Obj render");
  window.setFramerateLimit(144);

  while(window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Z:
            rotspeedy = (rotspeedy + 1) % 11;
            rot = Matrix4::rotateY((M_PI*(0.2*rotspeedy))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::X:
            rotspeedy = (rotspeedy - 1) % 11;
            rot = Matrix4::rotateY((M_PI*(0.2*rotspeedy))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::V:
            rotspeedx = (rotspeedx + 1) % 11;
            rot = Matrix4::rotateX((M_PI*(0.2*rotspeedx))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::C:
            rotspeedx = (rotspeedx - 1) % 11;
            rot = Matrix4::rotateX((M_PI*(0.2*rotspeedx))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::B:
            rotspeedz = (rotspeedz + 1) % 11;
            rot = Matrix4::rotateZ((M_PI*(0.2*rotspeedz))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::N:
            rotspeedz = (rotspeedz - 1) % 11;
            rot = Matrix4::rotateZ((M_PI*(0.2*rotspeedz))/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::E:
            scalex = 1.1;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scalex = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::R:
            scalex = 0.9;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scalex = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::T:
            scaley = 1.1;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scaley = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::Y:
            scaley = 0.9;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scaley = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::U:
            scalez = 1.1;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scalez = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::I:
            scalez = 0.9;
            scale = Matrix4::scale(scalex, scaley, scalez);
            transf = gentransf(rot, trans, scale);
            modelo1.transform(transf);
            scale = Matrix4();
            scalez = 1.0;
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::W:
            speedx = speedx + 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::S:
            speedx = speedx - 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::A:
            speedz = speedz + 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::D:
            speedz = speedz - 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::K:
            speedy = speedy - 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::L:
            speedy = speedy + 0.1;
            trans = Matrix4::translate(speedx/144, speedy/144, speedz/144);
            transf = gentransf(rot, trans, scale);
            break;
          case sf::Keyboard::Space:
            cam = Vector3(cam.x, cam.y+1.0, cam.z);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          case sf::Keyboard::LShift:
          case sf::Keyboard::RShift:
            cam = Vector3(cam.x, cam.y-1.0, cam.z);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          case sf::Keyboard::Left:
            cam = Vector3(cam.x, cam.y, cam.z-1.0);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          case sf::Keyboard::Right:
            cam = Vector3(cam.x, cam.y, cam.z+1.0);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          case sf::Keyboard::Up:
            cam = Vector3(cam.x-1.0, cam.y, cam.z);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          case sf::Keyboard::Down:
            cam = Vector3(cam.x+1.0, cam.y, cam.z);
            look = Matrix4::lookAt(cam, centroCubo, Vector3(0, 1, 0));
            vista = Matrix4::multiply(look, persp);
            break;
          default:
            // window.close();
            break;
        }
      }
    }

    img1.clear();

    modelo1.transform(transf);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        ejesimg[i][j] = vista.multiplyVector(ejes[i][j]);
      }
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        double w = ejesimg[i][j].w;
        ejesimg[i][j] = Vector4(ejesimg[i][j].x/w, ejesimg[i][j].y/w, ejesimg[i][j].z, ejesimg[i][j].w);
      }
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        int x = (ejesimg[i][j].x + 1)/2 * img1.width;
        int y = (ejesimg[i][j].y + 1)/2 * img1.height;
        img1.fillpoint(x, y, colors[i], 5);
      }
    }

    for (int i = 0; i < 3; i++) {
      int x = (ejesimg[i][0].x + 1)/2 * img1.width;
      int y = (ejesimg[i][0].y + 1)/2 * img1.height;
      int x2 = (ejesimg[i][1].x + 1)/2 * img1.width;
      int y2 = (ejesimg[i][1].y + 1)/2 * img1.height;
      img1.bresenham({x, y}, {x2, y2}, colors[i]);
    }

    modelo1.toScreen(vista, img1.width, img1.height);
    for (size_t i = 0; i < modelo1.pixeles.size(); i += (1 << optimize))
    {
      img1.putPixel(modelo1.pixeles[i].first, modelo1.pixeles[i].second, 0xFFFFFFFF);
      // img1.fillpoint(modelo1.pixeles[i].first, modelo1.pixeles[i].second, colors[i%13], 4);
    }

    for (size_t i = 0; i < modelo1.caras.size(); i += (1 << optimize))
    {
      vector<int> cara = modelo1.caras[i];

      size_t i1 = modelo1.indiceVerticeCara(cara, 0);
      size_t i2 = modelo1.indiceVerticeCara(cara, 1);
      size_t i3 = modelo1.indiceVerticeCara(cara, 2);
      Vector3 v1 = Vector4::subtract(modelo1.verticesCam[i2-1], modelo1.verticesCam[i1-1]).toVector3();
      Vector3 v2 = Vector4::subtract(modelo1.verticesCam[i3-1], modelo1.verticesCam[i1-1]).toVector3();

      Vector3 norm = Vector3::cross(v1, v2);

      if (norm.z < 0)
        continue;

      for (size_t j = 1; j < cara.size(); j++)
      {
        size_t i1 = modelo1.indiceVerticeCara(cara, j-1);
        size_t i2 = modelo1.indiceVerticeCara(cara, j);
        pair<int, int> p1 = modelo1.pixeles[i1-1];
        pair<int, int> p2 = modelo1.pixeles[i2-1];
        int x1 = p1.first;
        int y1 = p1.second;
        int x2 = p2.first;
        int y2 = p2.second;

        if (x1 < 0 || x1 >= img1.width || x2 < 0 || x2 >= img1.width || y1 < 0 || y1 >= img1.width || y2 < 0 || y2 >= img1.width)
          continue;

        img1.bresenham({x1, y1}, {x2, y2}, colors[6]);

        if (j == cara.size()-1)
        {
          size_t i1 = modelo1.indiceVerticeCara(cara, j);
          size_t i2 = modelo1.indiceVerticeCara(cara, 0);
          pair<int, int> p1 = modelo1.pixeles[i1-1];
          pair<int, int> p2 = modelo1.pixeles[i2-1];
          int x1 = p1.first;
          int y1 = p1.second;
          int x2 = p2.first;
          int y2 = p2.second;
          img1.bresenham({x1, y1}, {x2, y2}, colors[6]);
        }
      }
    }

    sf::Texture texture;
    texture.create(img1.width, img1.height);
    texture.update(img1.toBuffer().data);

    sf::Sprite sprite(texture);

    window.clear();
    window.draw(sprite);
    window.display();
  }


  return 0;
}
