#include "vector2.h"
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;

#define isAlpha(c) ('A'<=c && c<='Z')||('a'<=c && c<='z')
#define isNumeric(c) ('0'<=c && c<='9')||(c=='.')
#define isOp(c) (c=='+' || c=='-' || c=='*' || c=='%' || c=='/' || c=='(' || c==')')

enum tokenType {
	SCALAR,
	VECTOR,
	OPERATOR
};

struct token {
	union {
		char op;
		float f;
		Vector2 v;
	};
	tokenType type;
	token(float f=0): type(SCALAR) {
		this->f = f;
	}
	token(Vector2 v): type(VECTOR) {
		this->v = v;
	}
	token(char op): type(OPERATOR) {
		this->op = op;
	}
};

std::ostream& operator<<(std::ostream& os, const token& t) {
	if(t.type==SCALAR)
		os << t.f;
	else if(t.type==VECTOR)
		os << t.v;
	else if(t.type==OPERATOR)
		os << t.op;
	return os;
}

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
	getline(cin, eq);
	while(getline(cin, eq))
	{
		vector<token> t;
		
		// parsing the equation
		string tokenName;
		bool valid = true;
		for(int i=0; i<=eq.length(); i++)
		{
			if(tokenName.length()>0)
			{
				if(isAlpha(tokenName[0]) && (i==eq.length() || (isNumeric(eq[i])||isOp(eq[i])||eq[i]==' '))) {
					if(t.size()>0 && (t.back().type!=OPERATOR || t.back().op==')'))	t.push_back(token('s'));
					
					if(variable.find(tokenName)==variable.end())
					{
						valid = false;
						cout << "INVALID: '" << tokenName << "' is not defined!" << endl;
					} else {
						token temp(variable[tokenName]);
						t.push_back(temp);
					}
					tokenName = "";
				} else if(isNumeric(tokenName[0]) && (i==eq.length() || (isAlpha(eq[i])||isOp(eq[i])||eq[i]==' '))) {
					if(t.size()>0 && (t.back().type!=OPERATOR || t.back().op==')'))	t.push_back(token('s'));
					
					istringstream stream(tokenName);
					float f; stream >> f;
					token temp(f);
					t.push_back(temp);
					tokenName = "";
				}
			}
			if(isNumeric(eq[i]) || isAlpha(eq[i]))
				tokenName += eq[i];
			else if(isOp(eq[i])) {
				if(eq[i]=='(' && t.size()>0 && (t.back().type!=OPERATOR || t.back().op==')')) {
					t.push_back(token('s'));
				}
				t.push_back(token(eq[i]));
			}
		}
		
		for(int i=0; i<t.size(); i++){
			token& temp = t[i];
			cout << temp << " ";
		}
		cout << endl;
	}

	return 0;
}