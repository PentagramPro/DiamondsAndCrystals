#include "Vector2d.h"





Vector2d::Vector2d(float x, float y) : x(x), y(y)
{
}

Vector2d::~Vector2d()
{
}

float Vector2d::Normalize()
{
	float len = Magnitude();
	if (len!=0.0)
	{
		x/=len;
		y/=len;
	}

	return len;
}

float Vector2d::Magnitude() const
{
	return sqrtf(x*x + y*y);
}



Vector2d & Vector2d::operator+=(const Vector2d & v2)
{
	x += v2.x;
	y += v2.y;

	return *this;
}

Vector2d & Vector2d::operator-=(const Vector2d & v2)
{
	x -= v2.x;
	y -= v2.y;

	return *this;
}

Vector2d & Vector2d::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2d & Vector2d::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

const Vector2d Vector2d::operator+(const Vector2d & v2) const
{
	return Vector2d(*this) += v2;
}

const Vector2d Vector2d::operator-(const Vector2d & v2) const
{
	return Vector2d(*this) -= v2;
}

const Vector2d Vector2d::operator*(const float scalar) const
{
	return Vector2d(*this) *= scalar;
}

const Vector2d Vector2d::operator/(const float scalar) const
{
	return Vector2d(*this) /= scalar;
}

bool Vector2d::operator==(const Vector2d & v2) const
{
	return ((x == v2.x) && (y == v2.y));
}

bool Vector2d::operator!=(const Vector2d & v2) const
{
	return !((x == v2.x) && (y == v2.y));
}
