#pragma once

#include "matrix.h"

struct Vector
{
	double x, y, z,h;

	Vector();
	Vector(const Vector& v);
	Vector(double x, double y, double z,double h=1.0f);
	Vector(double f);

	virtual ~Vector();

	inline double length2();
	inline double length();

	double normalize();
	Vector normalized();

	Vector& operator =(const Vector& v);
	Vector& operator +=(const Vector& v);
	Vector& operator -=(const Vector& v);
	Vector& operator *=(double f);
	Vector& operator /=(double f);
	Vector operator -() const;
};

double dot(Vector v1, Vector v2);
Vector cross(Vector v1, Vector v2);

inline Vector operator +(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

inline Vector operator *(Matrix& m, Vector& v)
{
	double temp[] = {v.x,v.y,v.z,v.h};
	double  ans[4]={0};
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			ans[i]+=m(i,j)*temp[j];
		}
	}
	return Vector(ans[0],ans[1],ans[2],ans[3]);
}

inline Vector operator -(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

inline Vector operator *(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

inline Vector operator *(const Vector& v, double f)
{
	return Vector(v.x * f,
		v.y * f,
		v.z * f);
}

inline Vector operator *(double f, const Vector& v)
{
	return Vector(f * v.x,
		f * v.y,
		f * v.z);
}

inline Vector operator /(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

inline Vector operator /(const Vector& v, double f)
{
	return Vector(v.x / f,
		v.y / f,
		v.z / f);
}

inline Vector operator /(double f, const Vector& v)
{
	return Vector(f / v.x,
		f / v.y,
		f / v.z);
}

typedef Vector Point;

struct Vector2
{
	double u, v;

	Vector2();
	Vector2(const Vector2& v);
	Vector2(double u, double v);
	Vector2(double f);

	virtual ~Vector2();

	Vector2& operator =(const Vector2& v);
};