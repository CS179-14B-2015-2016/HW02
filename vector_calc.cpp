#include "vector2.h"
#include "token.h"
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <queue>
#include <cassert>
using namespace std;

#define isAlpha(c) ('A'<=c && c<='Z')||('a'<=c && c<='z')
#define isNumeric(c) ('0'<=c && c<='9')||(c=='.')
#define isOp(c) (c=='+' || c=='-' || c=='*' || c=='%' || c=='/' || c=='(' || c==')')

int operatorPrecedence(const char& op) {
	switch(op) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 1;
		case '%': return 1;
		case '/': return 1;
		case 's': return 2;
	}
	return 1;
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
		
		// tokenizing the equation
		string tokenName;
		bool valid = true;
		for(int i=0; i<=eq.length() && valid; i++)
		{
			if(tokenName.length()>0)
			{
				if(isAlpha(tokenName[0]) && (i==eq.length() || (isNumeric(eq[i])||isOp(eq[i])||eq[i]==' '))) {
					if(t.size()>0 && (t.back().type!=OPERATOR || t.back().op==')'))	t.push_back(token('s'));
					
					if(variable.find(tokenName)==variable.end())
					{
						cout << "INVALID: '" << tokenName << "' is not defined!" << endl;
						valid = false;
						break;
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
		if(!valid) break;
		
		// shunting yard
		queue<token> postfix;
		vector<token> opStack;
		
		for(int i=0; i<t.size() && valid; i++)
		{
			if(t[i].type!=OPERATOR)
				postfix.push(t[i]);
			else if(t[i].op=='(') {
				opStack.push_back(t[i]);
			}
			else if(t[i].op==')') {
				bool finish = false;
				while(!finish) {
					if(opStack.empty()) {
						cout << "INVALID: mismatched parenthesis"<< endl;
						valid = false;
						break;
					}
					
					token last = opStack.back();
					opStack.pop_back();
					if(last.op=='(')
						finish = true;
					else
						postfix.push(last);
				}
			}
			else {
				while(!opStack.empty()) {
					token last = opStack.back();
					if(last.op!='(' && operatorPrecedence(t[i].op)<=operatorPrecedence(last.op)) {
						opStack.pop_back();
						postfix.push(last);
						continue;
					}
					break;
				}
				opStack.push_back(t[i]);
			}
		}
		if(!valid) continue;
		
		while(!opStack.empty()){
			postfix.push(opStack.back());
			opStack.pop_back();
		}
		
		// evaluation
		vector<token> valueStack;
		while(!postfix.empty() && valid)
		{
			token curr = postfix.front();
			postfix.pop();
			if(curr.type!=OPERATOR) {
				valueStack.push_back(curr);
				continue;
			}
			
			char currOp = curr.op;
			if(currOp=='s') currOp = '*';
			
			if(valueStack.size()<2)
			{
				valid = false;
				cout << "INVALID: pairing of values failed" << endl;
				break;
			}
			token rhs = valueStack.back();
			valueStack.pop_back();
			token lhs = valueStack.back();
			valueStack.pop_back();
			
			token next = operate(lhs, rhs, currOp, &valid);
			if(!valid) cout << "INVALID" << endl;
			valueStack.push_back(next);
		}
		if(!valid) continue;
		
		assert(valueStack.size()==1);
		token result = valueStack.back();
		cout << result << endl;
	}

	return 0;
}