#include <cmath>

#include "vectormath.h"

Vector::Vector()
	: x(0.0f),
	y(1.0f),
	z(0.0f),
	h(0.0f)

{
}

Vector::Vector(const Vector& v)
	: x(v.x),
	y(v.y),
	z(v.z),
	h(v.h)
{
}

Vector::Vector(double x, double y, double z, double h)
	: x(x),
	y(y),
	z(z),
	h(h)
{
}

Vector::Vector(double f)
	: x(f),
	y(f),
	z(f),
	h(1)
{
}

Vector::~Vector()
{
}

inline double Vector::length2()
{
	return (x*x + y*y + z*z)/(h*h);
}

inline double Vector::length()
{
	return std::sqrt(length2());
}

double Vector::normalize()
{
	double l = length();

	*this /= l;

	return l;
}

Vector Vector::normalized()
{
	Vector v(*this);
	v.normalize();
	return v;
}

double dot(Vector v1, Vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)/(v1.h*v2.h);
}

Vector cross(Vector v1, Vector v2)
{
	return Vector(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,v1.h*v2.h);

}

Vector& Vector::operator =(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	h = v.h;

	return *this;
}

Vector& Vector::operator +=(const Vector& v)
{
	x += v.x * (h/v.h);
	y += v.y * (h/v.h);
	z += v.z * (h/v.h);
	return *this;
}

Vector& Vector::operator -=(const Vector& v)
{
	x -= v.x * (h/v.h);
	y -= v.y * (h/v.h);
	z -= v.z * (h/v.h);
	return *this;
}

Vector& Vector::operator *=(double f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector& Vector::operator /=(double f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

Vector Vector::operator -() const
{
	return Vector(-x, -y, -z);
}

Vector2::Vector2()
	: u(0.0f),
	v(0.0f)
{
}

Vector2::Vector2(const Vector2 &v)
	: u(v.u),
	v(v.v)
{
}

Vector2::Vector2(double u, double v)
	: u(u),
	v(v)
{
}

Vector2::Vector2(double f)
	: u(f),
	v(f)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator =(const Vector2& v)
{
	u = v.u;
	this->v = v.v;
	return *this;
}