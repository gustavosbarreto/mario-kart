#include "Vector.h"

Vector::Vector()
{
}

Vector::Vector(double x, double y):
	x(x), y(y)
{
}

Vector Vector::operator+(const Vector &v)
{
	return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector &v)
{
	return Vector(x - v.x, y - v.y);
}

Vector Vector::operator-()
{
	return Vector(-x, -y);
}

Vector Vector::operator+=(const Vector &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector Vector::operator-=(const Vector &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector Vector::operator*(double e)
{
	return Vector(x * e, y * e);
}

Vector Vector::operator/(double e)
{
	return Vector(x / 2, y / 2);
}

Vector Vector::operator*(double e, const Vector &v)
{
	return Vector(v.x * e, v.y * e);
}
