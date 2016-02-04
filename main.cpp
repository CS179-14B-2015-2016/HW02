//
//  main.cpp
//  Vector Calculator
//
//  Created by Michelle Ann Parlan on 2/3/16.
//  Copyright (c) 2016 Michelle Ann Parlan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;
using std::cout;
using std::cin;
using std::ostream;
using std::istream;

char opA;
char opB;
char operation;
string final;

class Vector2
{
public:
    char name;
    float x, y;
    Vector2(char name = ' ', float x = 0, float y = 0) :name(name), x(x),y(y)
    {}
    
    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(name, x + v.x, y + v.y);
    }
    
    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(name, x - v.x, y - v.y);
    }
    
    Vector2 operator*(const float s) const  {
        return Vector2(name, s * x, s * y);
    }
    
    Vector2 operator/(const float s) const  {
        return Vector2(name, x / s, y / s);
    }
    
    float operator*(const Vector2 &v) const {
        return x * v.x + y * v.y;
    }
    
    float operator%(const Vector2 &v) const {
        return x * v.y - y * v.x;
    }
    
    ostream& toStream(ostream& os) const;
    istream& fromStream(istream& is);
};

ostream& operator<<(ostream& os, const Vector2& v); //do not change data
istream& operator>>(istream& is, Vector2& v); //modify Vector2 values


/*bool isOperator(const char& c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
    {
        return true;
    }
    else
    {
        return false;
    }
}*/


ostream& Vector2::toStream(ostream& os)const //print out
{
    os << x << " " << y << endl;
    
    return os;
}

istream& Vector2::fromStream(istream& is) //accept & store value
{
    is >> name >> x >> y;
    
    return is;
}

ostream& operator<<(ostream& os, Vector2& v)
{
    return(v.toStream(os));
}

istream& operator>>(istream& is, Vector2& v)
{
    return(v.fromStream(is));
}


int main()
{
    Vector2 vecA;
    Vector2 vecB;
    Vector2 vecAns;
    
    while(cin.peek() != '=')
    {
        cin >> vecA >> vecB;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// do not end
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// do not end

    while (true)
    {
        cin >> opA >> operation >> opB;
        
        stringstream sA, sB;
        float ans;
        float iA, iB;
        sA << opA;
        sA >> iA;
        sB << opB;
        sB >> iB;
        
        cout << setiosflags(ios::fixed | ios::showpoint);
        cout << setprecision(1);
        
        if (isalpha(opA) && isalpha(opB)) //both vectors
        {
            if (operation == '+')
            {
                vecAns = vecA + vecB;
                cout << vecAns << endl;
            }
            else if (operation == '-')
            {
                if (vecA.name == opA)
                {
                    vecAns = vecA - vecB;
                    cout << vecAns << endl;
                }
                else if (vecB.name == opA)
                {
                    vecAns = vecB - vecA;
                    cout << vecAns << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else if (operation == '*') //Dot Product
            {
                ans = vecA * vecB;
                cout << ans << endl;
            }
            else if (operation == '%') //Cross Product
            {
                if (vecA.name == opA)
                {
                    ans = vecA % vecB;
                    cout << ans << endl;
                }
                else if (vecB.name == opA)
                {
                    ans = vecB % vecA;
                    cout << ans << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else
            {
                final = "INVALID";
                cout << final << endl;
            }

        }
        else if (isalpha(opA) && (!isalpha(opB))) //vector & scalar
        {
            if (vecA.name == opA)
            {
                if (operation == '*') //Scalar Multiplication
                {
                    vecAns = vecA * iB;
                    cout << vecAns << endl;
                }
                else if (operation == '/')//Scalar Division
                {
                    vecAns = vecA / iB;
                    cout << vecAns << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else if (vecB.name == opA)
            {
                if (operation == '*') //Scalar Multiplication
                {
                    vecAns = vecB * iB;
                    cout << vecAns << endl;
                }
                else if (operation == '/')//Scalar Division
                {
                    vecAns = vecB / iB;
                    cout << vecAns << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else
            {
                final = "INVALID";
                cout << final << endl;
            }

        }
        else if ((!isalpha(opA)) && isalpha(opB)) //scalar & vector
        {
            if (vecA.name == opB)
            {
                if (operation == '*')//Scalar Multiplication
                {
                    vecAns = vecA * iA;
                    cout << vecAns << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else if (vecB.name == opB)
            {
                if (operation == '*')//Scalar Multiplication
                {
                    vecAns = vecB * iA;
                    cout << vecAns << endl;
                }
                else
                {
                    final = "INVALID";
                    cout << final << endl;
                }
            }
            else
            {
                final = "INVALID";
                cout << final << endl;
            }
        }
        else //both scalar
        {
            if (operation == '+')
            {
                ans = iA + iB;
                cout << ans << endl;
            }
            else if (operation == '-')
            {
                ans = iA - iB;
                cout << ans << endl;
            }
            else if (operation == '*')
            {
                ans = iA * iB;
                cout << ans << endl;
            }
            else if (operation == '/')
            {
                ans = iA / iB;
                cout << ans << endl;
            }
            else
            {
                final = "INVALID";
                cout << final << endl;
            }
        }
        
        cout << endl;
    }
    
    return 0;
}
