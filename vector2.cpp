#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template<class T>
class vector2
{
	public:
	string name;
	T x;
	T y;
	

	//vector addition
	vector2& operator+(const vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	//vector subtraction
	vector2& operator-(const vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	//cross product
	float& operator%(const vector2& v)
	{
		return ((x * v.y)-(y * v.x));
	}
	//dot product
	float& operator*(const vector2& v)
	{
		return ((x * v.x)+(y * v.y));
	}
	//scalar multiplication
	vector2& operator*(const T& s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	//scalar division
	vector2& operator/(const T& s)
	{
		x /= s;
		y /= s;
		return *this;
	}
};


int main(int argc, char** argv)
{
	
	
}
