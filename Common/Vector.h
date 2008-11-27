#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>

class Vector
{
private:
	double mX;
	double mY;

public:
	Vector();
	Vector(double x, double y);

	Vector operator+(const Vector &v);
	Vector operator-(const Vector &v);
	Vector operator-();
	Vector operator+=(const Vector &v);
	Vector operator-=(const Vector &v);
	Vector operator*(double e);
	Vector operator/(double e);

	friend Vector operator*(double e, const Vector &v);

	inline double x() const { return mX; }
	inline double y() const { return mY; }
	inline double length() const { return sqrt(mX * mX + mY * mY); }
};

#endif
