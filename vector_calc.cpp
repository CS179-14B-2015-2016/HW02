#include "vector2.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct value {
	bool isVector;
	float f;
	Vector2 v;
	value(): f(0), isVector(false) {}
	value(float f): f(f),  isVector(false) {}
	value(Vector2 v): v(v), isVector(true) {}
};

void operate(value& val, value& temp, char op, bool* success)
{
	switch(op) {
		case '+':
			if(val.isVector && temp.isVector)
			{
				val.v = val.v + temp.v;
			} else if(!val.isVector && !temp.isVector) {
				val.f = val.f + temp.f;
			}else
				*success = false;
			break;
		case '-':
			if(val.isVector && temp.isVector)
			{
				val.v = val.v - temp.v;
			} else if(!val.isVector && !temp.isVector) {
				val.f = val.f - temp.f;
			} else
				*success = false;
			break;
		case '*':
			if(val.isVector && temp.isVector)
			{
				val.isVector = false;
				val.f = val.v*temp.v;
			} else if(val.isVector) {
				val.v = val.v*temp.f;
			} else if(temp.isVector) {
				val.isVector = true;
				val.v = val.f*temp.v;
			} else {
				val.f *= temp.f;
			}
			break;
		case '/':
			if(val.isVector && !temp.isVector)
			{
				val.v = val.v/temp.f;
			} else if(!val.isVector && !temp.isVector) {
				val.f /= temp.f;
			}
			else
				*success = false;
			break;
		case '%':
			if(val.isVector && temp.isVector) {
				val.isVector = false;
				val.f = val.v%temp.v;
			} else
				*success = false;
			break;
	}
}

map<string, Vector2> variable;
value compute(const string& s, bool* success);

value evaluate(const string& s, bool* success) {
	bool isExp = false;
	for(int i=0; i<s.length(); i++){
		if(isspace(s[i])) {
			isExp = true;
			break;
		}
	}
	
	if(isExp)
		return compute(s, success);
	
	bool isNum = false;
	bool isVec = false;
	for(int i=0; i<s.length(); i++)
	{
		if(('A' <= s[i] && s[i] <= 'Z') || ('a' <= s[i] && s[i] <='z')) {
			isVec = true;
		} else {
			isNum = true;
		}
		if(isVec && isNum) break;
	}
	
	if(isVec && isNum) {
		vector<value> factors;
		
		bool currentV = (('A' <= s[0] && s[0] <= 'Z') || ('a' <= s[0] && s[0] <='z'));
		string parser = "";
		for(int i=0; i<s.length(); i++)
		{
			if(('A' <= s[i] && s[i] <= 'Z') || ('a' <= s[i] && s[i] <='z')) {
				if(!currentV) {
					float f; istringstream(parser)>>f;
					factors.push_back(value(f));
					parser = "";
				}
			} 
			else if(currentV) {
				if(variable.find(parser)==variable.end())
				{
					*success = false;
					return value();
				}
				
				factors.push_back(value(variable[parser]));
				parser = "";
			}
			parser += s[i];
		}
		
		value val = factors[0];
		for(int i=1; i<factors.size(); i++) {
			value curr = factors[i];
			operate(val, curr, '*', success);
		}
		return val;
		
	} else if (isVec) {
		if(variable.find(s)==variable.end())
		{
			*success = false;
			return value();
		}
		
		Vector2 v = variable[s];
		return value(v);
	} else {
		float f; istringstream(s)>>f;
		//cout << f << endl;
		return value(f);
	}
}

value compute(const string& s, bool* success)
{
	*success = true;
	value val;
	int n = s.size();
	vector<string> terms;
	
	string p = "";
	for(int i=0; i<n; i++)
	{
		if(s[i]==' '){
			if(p.length()>0) {
				terms.push_back(p);
				p = "";
			}
		} else if(s[i]=='(') {
			if(p.length()>0) {
				terms.push_back(p);
				p = "";
			}
			
			int balance = 1;
			while(i<n && balance!=0) {
				i++;
				if(s[i]=='(') balance++;
				else if(s[i]==')') balance--;
				
				if(balance==0) break;
				p += s[i];
			}
			terms.push_back(p);
			p = "";
		} else {
			p += s[i];
		}
	}
	
	if(p.length()>0) {
		terms.push_back(p);
		p = "";
	}
	
	/*
	for(int i=0; i<terms.size(); i++)
		cout << i << "--: " << terms[i] << endl;
	*/
	val = evaluate(terms[0], success);
	for(int i=2; i<terms.size(); i+=2) {
		char operation = terms[i-1][0];
		value temp = evaluate(terms[i], success);
		//cout << terms[i] << " = " << temp.isVector << endl;
		operate(val, temp, operation, success);
		if(!success) return val;
	}
	return val;
}

int main()
{

	// saving the input
	string name;
	while(cin>>name && name!="=")
	{
		float x, y;
		cin >> x >> y;
		if(variable.find(name)!=variable.end())
			cout << "INVALID: VARIABLE NAME USED" << endl;
		else {
			variable[name] = Vector2(x, y);
		}
	}

	string eq;
	while(getline(cin, eq))
	{
		if(eq.length()==0) continue;
		cout << eq << endl;
		bool success;
		value val = compute(eq, &success);
		if(!success)
			cout << "INVALID" << endl;
		else if(val.isVector)
			cout << val.v.x << " " << val.v.y << endl;
		else
			cout << val.f << endl;
	}

	return 0;
}