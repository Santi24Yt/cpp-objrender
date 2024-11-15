#include <cmath>
#include "vecmatriz.h"

/**
 * @brief Normaliza el vector actual.
 * @return Vector normalizado.
 */
Vector3 Vector3::normalize() const {
  double norma = sqrt(
    pow(x, 2) +
    pow(y, 2) +
    pow(z, 2)
  );
  return Vector3(x/norma, y/norma, z/norma);
}

/**
  * @brief Devuelve la matriz adjunta de la matriz actual.
  * @return Matrix4 Matriz adjunta.
  */
Matrix4 Matrix4::adjoint() const {
  return Matrix4(
    a11*a22*a33 - a11*a23*a32 - a12*a21*a33 + a12*a23*a31 + a13*a21*a32 - a13*a22*a31,
    -a01*a22*a33 + a01*a23*a32 + a02*a21*a33 - a02*a23*a31 - a03*a21*a32 + a03*a22*a31,
    a01*a12*a33 - a01*a13*a32 - a02*a11*a33 + a02*a13*a31 + a03*a11*a32 - a03*a12*a31,
    -a01*a12*a23 + a01*a13*a22 + a02*a11*a23 - a02*a13*a21 - a03*a11*a22 + a03*a12*a21,

    -a10*a22*a33 + a10*a23*a32 + a12*a20*a33 - a12*a23*a30 - a13*a20*a32 + a13*a22*a30,
    a00*a22*a33 - a00*a23*a32 - a02*a20*a33 + a02*a23*a30 + a03*a20*a32 - a03*a22*a30,
    -a00*a12*a33 + a00*a13*a32 + a02*a10*a33 - a02*a13*a30 - a03*a10*a32 + a03*a12*a30,
    a00*a12*a23 - a00*a13*a22 - a02*a10*a23 + a02*a13*a20 + a03*a10*a22 - a03*a12*a20,

    a10*a21*a33 - a10*a23*a31 - a11*a20*a33 + a11*a23*a30 + a13*a20*a31 - a13*a21*a30,
    -a00*a21*a33 + a00*a23*a31 + a01*a20*a33 - a01*a23*a30 - a03*a20*a31 + a03*a21*a30,
    a00*a11*a33 - a00*a13*a31 - a01*a10*a33 + a01*a13*a30 + a03*a10*a31 - a03*a11*a30,
    -a00*a11*a23 + a00*a13*a21 + a01*a10*a23 - a01*a13*a20 - a03*a10*a21 + a03*a11*a20,

    -a10*a21*a32 + a10*a22*a31 + a11*a20*a32 - a11*a22*a30 - a12*a20*a31 + a12*a21*a30,
    a00*a21*a32 - a00*a22*a31 - a01*a20*a32 + a01*a22*a30 + a02*a20*a31 - a02*a21*a30,
    -a00*a11*a32 + a00*a12*a31 + a01*a10*a32 - a01*a12*a30 - a02*a10*a31 + a02*a11*a30,
    a00*a11*a22 - a00*a12*a21 - a01*a10*a22 + a01*a12*a20 + a02*a10*a21 - a02*a11*a20
  );
}

/**
  * @brief Calcula el determinante de la matriz.
  * @return double Determinante de la matriz.
  */
double Matrix4::determinant() const {
    return a00*a11*a22*a33 - a00*a11*a23*a32 - a00*a12*a21*a33 + a00*a12*a23*a31 + a00*a13*a21*a32 - a00*a13*a22*a31
         - a01*a10*a22*a33 + a01*a10*a23*a32 + a01*a12*a20*a33 - a01*a12*a23*a30 - a01*a13*a20*a32 + a01*a13*a22*a30
         + a02*a10*a21*a33 - a02*a10*a23*a31 - a02*a11*a20*a33 + a02*a11*a23*a30 + a02*a13*a20*a31 - a02*a13*a21*a30
         - a03*a10*a21*a32 + a03*a10*a22*a31 + a03*a11*a20*a32 - a03*a11*a22*a30 - a03*a12*a20*a31 + a03*a12*a21*a30;
}

/**
  * @brief Multiplica la matriz por un escalar.
  * @param scalar Escalar por el cual multiplicar la matriz.
  * @return Matrix4 Resultado de la multiplicación por el escalar.
  */
Matrix4 Matrix4::multiplyByScalar(double scalar) const {
  return Matrix4(
    a00 * scalar, a01 * scalar, a02 * scalar, a03 * scalar,
    a10 * scalar, a11 * scalar, a12 * scalar, a13 * scalar,
    a20 * scalar, a21 * scalar, a22 * scalar, a23 * scalar,
    a30 * scalar, a31 * scalar, a32 * scalar, a33 * scalar
  );
}

/**
  * @brief Multiplica un vector por la matriz.
  * @param v Vector a multiplicar.
  * @return Vector4 Resultado de la multiplicación del vector por la matriz.
  */
Vector4 Matrix4::multiplyVector(const Vector4& v) const {
  return Vector4(
    a00*v.x + a10*v.y + a20*v.z + a30*v.w,
    a01*v.x + a11*v.y + a21*v.z + a31*v.w,
    a02*v.x + a12*v.y + a22*v.z + a32*v.w,
    a03*v.x + a13*v.y + a23*v.z + a33*v.w
  );
}
