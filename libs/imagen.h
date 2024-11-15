#ifndef IMAGEN_H
#define IMAGEN_H

typedef unsigned char byt;

// inline int min(int a, int b) {
//   if (a <= b)
//     return a;
//   return b;
// }
//
// inline int max(int a, int b) {
//   if (a >= b)
//     return a;
//   return b;
// }

struct punto {
  int x;
  int y;
  int z;
};

typedef struct punto Punto;

template <int widthT, int heightT>
class Imagen {
  public:
  Imagen()
  {
    fill(0x000000FF);
  }

  const int width = widthT;
  const int height = heightT;

  struct imgBuffer {
    byt data[heightT * widthT * 4];
    const int size = heightT * widthT * 4;
  };

  imgBuffer toBuffer() {
    struct imgBuffer buf;
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int pixel = image[y][x];
        int index = 4 * ((y*width) + x);
        buf.data[index + 0] = (pixel >> 24) & 0xFF;
        buf.data[index + 1] = (pixel >> 16) & 0xFF;
        buf.data[index + 2] = (pixel >> 8) & 0xFF;
        buf.data[index + 3] = (pixel >> 0) & 0xFF;
      }
    }
    return buf;
  }

  void putPixel(int x, int y, int c) {
    if (x >= 0 && x < width && y >= 0 && y < height)
      image[y][x] = c;
  }

  Imagen& fill(int color) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        putPixel(x, y, color);
      }
    }
    return *this;
  }

  Imagen& fillrect(int xs, int ys, int w, int h, int c) {
    for (int x = xs; x < xs + w; x++) {
      for (int y = ys; y < ys + h; y++) {
        putPixel(x, y, c);
      }
    }
    return *this;
  }

  Imagen& fillrectc(int xs, int ys, int w, int h, int c) {
    int hw = w/2;
    int hh = h/2;
    return fillrect(xs-hw, ys-hh, w, h, c);
  }

  Imagen& fillpoint(int x, int y, int c, int size = 1) {
    return fillrectc(x, y, size, size, c);
  }

  void clear() {
    fill(0x000000FF);
  }


  double absd(double n) {
    if (n >= 0) {
      return n;
    } else {
      return -n;
    }
  }

  void bresenham(Punto pi, Punto pf, int c) {
    if (absd(pf.x - pi.x) > absd(pf.y - pi.y)) {
      _bresenhamH(pi, pf, c);
    } else {
      _bresenhamV(pi, pf, c);
    }
  }


  private:
  int image[heightT][widthT];

  void _bresenhamH(Punto pi, Punto pf, int c) {
    if (pi.x > pf.x) {
      Punto t = pi;
      pi = pf;
      pf = t;
    }
    
    int dx = pf.x - pi.x;
    int dy = pf.y - pi.y;
    int dir = 1;
    if (dy < 0)
      dir = -1;
    dy *= dir;

    int D = 2*dy - dx;

    int y = pi.y;
    int x;

    for (int i = 0; i <= dx; i++) {
      x = pi.x + i;
      putPixel(x, y, c);
      // image[y][x] = c;

      if (D >= 0) {
        y += dir;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }

  void _bresenhamV(Punto pi, Punto pf, int c) {
    if (pi.y > pf.y) {
      Punto t = pi;
      pi = pf;
      pf = t;
    }
    
    int dx = pf.x - pi.x;
    int dy = pf.y - pi.y;
    int dir = 1;
    if (dx < 0)
      dir = -1;
    dx *= dir;

    int D = 2*dx - dy;

    int y;
    int x = pi.x;

    for (int i = 0; i <= dy; i++) {
      y = pi.y + i;
      putPixel(x, y, c);
      // image[y][x] = c;

      if (D >= 0) {
        x += dir;
        D = D - 2*dy;
      }
      D = D + 2*dx;
    }
  }

};

#endif
