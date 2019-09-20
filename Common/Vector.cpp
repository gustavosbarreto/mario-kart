#include "Vector.h"

Vector::Vector() : mX(0), mY(0) {}

Vector::Vector(double x, double y) : mX(x), mY(y) {}

Vector Vector::operator+(const Vector &v) {
  return Vector(mX + v.mX, mY + v.mY);
}

Vector Vector::operator-(const Vector &v) {
  return Vector(mX - v.mX, mY - v.mY);
}

Vector Vector::operator-() { return Vector(-mX, -mY); }

Vector Vector::operator+=(const Vector &v) {
  mX += v.mX;
  mY += v.mY;
  return *this;
}

Vector Vector::operator-=(const Vector &v) {
  mX -= v.mX;
  mY -= v.mY;
  return *this;
}

Vector Vector::operator*(double e) { return Vector(mX * e, mY * e); }

Vector Vector::operator/(double e) { return Vector(mX / 2, mY / 2); }

Vector operator*(double e, const Vector &v) {
  return Vector(v.mX * e, v.mY * e);
}
