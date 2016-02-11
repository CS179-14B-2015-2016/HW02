#ifndef vector2_H
#define vector2_H
#include<iostream>

class Vector2
{
public:
	float x, y;
	Vector2(): x(0), y(0) {}
	Vector2(float x, float y): x(x), y(y) {}

	// operator overloading
	Vector2 operator+(const Vector2& rhs) const {
		return Vector2(x+rhs.x, y+rhs.y);
	}

	Vector2 operator-(const Vector2& rhs) const {
		return Vector2(x-rhs.x, y-rhs.y);
	}

	Vector2 operator*(const float rhs) const {
		return Vector2(x*rhs, y*rhs);
	}

	Vector2 operator/(const float rhs) const {
		return Vector2(x/rhs, y/rhs);
	}

	float operator*(const Vector2& rhs) const {
		return (x*rhs.x)+(y*rhs.y);
	}

	float operator%(const Vector2& rhs) const {
		return (x*rhs.y)-(y*rhs.x);
	}
	
};

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
	os << v.x << " " << v.y;
	return os;
}

inline Vector2 operator*(const float lhs, const Vector2& rhs) {
	return rhs*lhs;
}
#endif