#pragma once
#include <math.h>

class Vector2d
{
public:
	Vector2d(float x = 0, float y = 0);
	virtual ~Vector2d();

	float Normalize();
	float Magnitude() const;
	static float Distance(const Vector2d& v1, const Vector2d& v2);

	Vector2d& operator+= (const Vector2d& v2);
	Vector2d& operator-= (const Vector2d& v2);
	Vector2d& operator*= (const float scalar);
	Vector2d& operator/= (const float scalar);

	const Vector2d operator+(const Vector2d &v2) const;
	const Vector2d operator-(const Vector2d &v2) const;
	const Vector2d operator*(const float scalar) const;
	const Vector2d operator/(const float scalar) const;

	//Vector2d& operator= (const Vector2d& v2);

	bool operator== (const Vector2d& v2) const;
	bool operator!= (const Vector2d& v2) const;

	float x, y;
};

