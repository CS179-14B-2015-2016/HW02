#include <iostream>
#include <fstream>
#include <string>
#include<cstring>
#include<stack>

using namespace std;

template<class T>
class vector2
{
	public:
	string name;
	T x;
	T y;
	
	//constructor
	vector2::vector2(string& derp, T& a, T&b)
	{
		name = derp;
		x = a;
		y = b;
	}
	
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

int priority(char ch) 
{
   switch (ch) 
   {
      case '*': return 4;
	  case '/': return 3;
      case '+': return 2;
      case '-': return 1;
      default : return 0;
   }
}

void postfixer(char infix[], char postfix[], int size) {
	stack<char> s;
	int weight;
	int i = 0;
	int k = 0;
	char ch;

	while (i < size) 
	{
		ch = infix[i];
		//for the parentheses
		if (ch == '(') 
		{
			s.push(ch);
			i++;
			continue;
		}
		if (ch == ')') 
		{
			while (!s.empty() && s.top() != '(') 
			{
				postfix[k++] = s.top();
				s.pop();
			}
			if (!s.empty()) 
			{
				s.pop();
			}
			i++;
			continue;
		}
		//check if operator or number
		weight = getWeight(ch);
		if (weight == 0) 
		{
			postfix[k++] = ch;
		}
		else 
		{
			if (s.empty()) 
			{
				s.push(ch);
			}
			else 
			{
				while (!s.empty() && s.top() != '(' && weight <= getWeight(s.top())) 
				{
					postfix[k++] = s.top();
					s.pop();
				}
				s.push(ch);
			}
		}
		i++;
	}
	while (!s.empty()) 
	{
		postfix[k++] = s.top();
		s.pop();
	}
	postfix[k] = 0;
}

int main(int argc, char** argv)
{
	string input;
	float xpos;
	float ypos;
	while(input != '=')
	{
		cin << input << xpos << ypos;
		vector2::vector2(input,xpos,ypos);
	}
   	//postfix things
   	/*
	int size = strlen(infix);
	char postfix[size];
	postifxer(infix,postfix,size);
	*/
	return 0;
	
	
}
