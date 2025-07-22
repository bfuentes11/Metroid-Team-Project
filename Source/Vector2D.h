#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>
struct Vector2D
{
	float x;
	float y;
	Vector2D operator-(const Vector2D& srcR)
	{
		return{ (x - srcR.x), (y - srcR.y) };

	}
	Vector2D& operator=(const Vector2D& src)
	{
		x = src.x;
		y = src.y;
		return *this;
	}
	Vector2D& operator+=(const Vector2D& src)
	{
		x += src.x;
		y += src.y;
		return *this;
	}
	Vector2D& operator*= (const int& src)
	{
		x *= src;
		y *= src;
		return *this;
	}
	Vector2D& operator-=(const Vector2D& src)
	{
		x -= src.x;
		y -= src.y;
		return *this;
	}
	friend bool operator<(const Vector2D& srcL, const Vector2D& srcR)
	{
		return srcL.x < srcR.x;
	}
	float length()
	{
		return (float)sqrt((double)x * x + (double)y * y);
	}
	void normalize()
	{
		float vectorLength = length();
		if (vectorLength != 0)
		{
			x /= vectorLength;
			y /= vectorLength;
		}

	}
	void vector2OtherPoint(Vector2D destination)
	{
		*this = { destination.x - x, destination.y - y };
	}
	void target(Vector2D targetPosition, int speed)
	{
		vector2OtherPoint(targetPosition);
		normalize();
		(*this) *= speed;
	}
};
#endif // !VECTOR2D_H

