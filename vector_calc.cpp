#include "vector2.h"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int main()
{
	map<string, Vector2> variable;

	// saving the input
	string name;
	while(cin>>name && name!="=")
	{
		float x, y;
		cin >> x >> y;
		if(variable.find(name)!=variable.end())
			cout << "INVALID: VARIABLE NAME USED" << endl;
		else
			variable[name] = Vector2(x, y);
	}

	string eq;
	while(getline(cin, eq))
	{
		// parsing the equation
	}

	return 0;
}