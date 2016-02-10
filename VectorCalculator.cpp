#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cctype>


// 123332 REVENTAR, Raphael Angelo S. 4BS CS-DGDD

using namespace std;
class Vect
{
public:
	double x, y;

	Vect(double x, double y) : x(x), y(y) {};


	Vect operator+(const Vect &rhs) const { //add
		return Vect(x + rhs.x, y + rhs.y);
	}

	Vect operator-(const Vect &rhs) const { //sub
		return Vect(x - rhs.x, y - rhs.y);
	}

	double operator*(const Vect &rhs) const { // dot prod
		return (x * rhs.x + y * rhs.y);
	}

	Vect operator*(const double &val) const { //scal mult
		return Vect(val * x, val * y);
	}

	Vect operator/(const double &val) const { // scal div
		return Vect(x / val, y / val);
	}

	double operator%(const Vect &rhs) const { //cross
		return (x*rhs.y - y*rhs.x);
	}


};

Vect operator*(const double &val, const Vect &rhs) {
	return Vect(val * rhs.x, val * rhs.y);
}

struct Value {
	enum Type { VECTOR, SCALAR, ERROR } type;
	union {
		double scal;
		Vect vec;
	};
	Value(const Vect &v) : type(VECTOR), vec(v) {}
	Value(const double &d) : type(SCALAR), scal(d){}
	Value() : type(ERROR), scal(-1.0) {}
};


struct Tokens {
	enum Token{OPERATOR,VECTOR,SCALAR} type;
	string token;
	Tokens(string s) : token(s){}
};

vector<string> getTokens(const string &input) {
	vector<string> tokens;
	string comps;
	stringstream stream(input);
	while (getline(stream, comps, ' ')) {
		tokens.push_back(comps);
	}
	return tokens;
};


bool isOperator(const char &c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return true;
	else
		return false;
};

bool isOpenPar(const char &c) {
	return c == '(';
};

bool isClosePar(const char &c) {
	return c == ')';
};

// helper functions from : https://gist.github.com/mycodeschool/7867739
int getOpWeight(const char &c) {
	int weight = -1;
	switch (c) {
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
	case '%':
		weight = 2;
	}
	return weight;
};


bool IsVector(const char &c) {
	return isalpha(c);
}


bool IsScalar(const char &c) {
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool HasHigherPrec(const char &top, const char &inc) {
	int topW = getOpWeight(top);
	int incW = getOpWeight(inc);
	if (topW == incW) {
		return true;
	}
	return topW > incW ? true : false;
};





Value EvalMe(const Value &o1,const Value &o2,const char &c){
	switch (c) {
	case'-':
		if ((o1.type == Value::Type::SCALAR && o2.type == Value::Type::VECTOR) || (o1.type == Value ::Type::VECTOR && o2.type == Value::Type::SCALAR))
			return Value();
		else if (o1.type == Value::Type::SCALAR)
			return Value(o1.scal - o2.scal);
		else
			return Value(o1.vec - o2.vec);
		break;
	case'+':
		if ((o1.type == Value::Type::SCALAR && o2.type == Value ::Type::VECTOR) || (o1.type == Value::Type::VECTOR && o2.type == Value::Type::SCALAR))
			return Value();
		else if (o1.type == Value::Type::SCALAR)
			return Value(o1.scal + o2.scal);
		else
			return Value(o1.vec + o2.vec);
		break;
	case'/':
		if (o2.type == Value::Type::VECTOR)
			return Value();
		else if (o1.type == Value::Type::SCALAR)
			return Value(o1.scal / o2.scal);
		else
			return Value(o1.vec / o2.scal);
		break;
	case'*':
		if (o1.type == Value::Type::SCALAR && o2.type == Value::Type::SCALAR) 
			return Value(o1.scal * o2.scal);
		else if (o1.type == Value::Type::SCALAR)
			return Value(o2.vec * o1.scal);
		else if (o2.type == Value::Type::SCALAR)
			return Value(o1.vec * o2.scal);
		else
			return Value(o1.vec * o2.vec);
		break;
	case'%':
		if (o1.type == Value::Type::SCALAR || o2.type == Value::Type::SCALAR)
			return Value();
		else
			return Value(o1.vec % o2.vec);
		break;
	}

	return Value();
}
int main() {
	string inputs = "";
	unordered_map<string, Vect> vects;
	//start
	while (true) {
		//get vectors as input
		getline(cin, inputs);
		if (inputs.find("=") == string::npos) {
			vector<string> tokens = getTokens(inputs);
			istringstream s(tokens[1]);
			double x;
			double y;
			s >> x;
			s.clear();
			s.str(tokens[2]);
			s >> y;
			Vect temp(x, y);
			vects.insert(make_pair(tokens[0], temp));
		}
		else {
			break;
		}
	}

	//postfix and evaluation

	while (getline(cin, inputs)) {
		stack<char> operand_stack;
		vector<Tokens> postfix_token;
		postfix_token.clear();
		string vec = "";
		string scal = "";
		bool addmult = false;
		bool addmult_end = false;
		for (char c : inputs) {
			if (c == ' ') continue;
			if (isOperator(c)) {
				if (vec.size() > 0) {
					Tokens temp(vec);
					temp.type = Tokens::VECTOR;
					postfix_token.push_back(temp);
					vec = "";
				}
				if (scal.size() > 0) {
					Tokens temp(scal);
					temp.type = Tokens::SCALAR;
					postfix_token.push_back(temp);
					scal = "";
				}
				while (!operand_stack.empty() && !isOpenPar(c) && HasHigherPrec(operand_stack.top(), c)) {
					string toAdd = "";
					toAdd += operand_stack.top();
					Tokens temp(toAdd);
					temp.type = Tokens::OPERATOR;
					postfix_token.push_back(temp);
					operand_stack.pop();
				}
				operand_stack.push(c);
				addmult = false;
				addmult_end = false;
			}
			else if (isOpenPar(c)) {
				if (addmult) {
					operand_stack.push('*');
				}
				addmult = false;
				addmult_end = false;
				operand_stack.push(c);
			}
			else if (isClosePar(c)) {
				if (vec.size() > 0) {
					Tokens temp(vec);
					temp.type = Tokens::VECTOR;
					postfix_token.push_back(temp);
					vec = "";
				}
				if (scal.size() > 0) {
					Tokens temp(scal);
					temp.type = Tokens::SCALAR;
					postfix_token.push_back(temp);
					scal = "";
				}
				while (!operand_stack.empty() && !isOpenPar(operand_stack.top())) {
					string toAdd = "";
					toAdd += operand_stack.top();
					Tokens temp(toAdd);
					temp.type = Tokens::OPERATOR;
					postfix_token.push_back(temp);
					operand_stack.pop();
				}
				operand_stack.pop();
				addmult = false;
				addmult_end = true;
			}
			else if (IsVector(c)) {
				if (scal.size() > 0) {
					Tokens temp(scal);
					temp.type = Tokens::SCALAR;
					postfix_token.push_back(temp);
					scal = "";
					operand_stack.push('*');
				}
				addmult = false;
				addmult_end = false;
				vec += c;
			}
			else { // scalar includes "."
				if (vec.size() > 0) {
					Tokens temp(vec);
					temp.type = Tokens::VECTOR;
					postfix_token.push_back(temp);
					vec = "";
					operand_stack.push('*');
				}
				if (addmult_end) {
					operand_stack.push('*');
				}

				addmult = true;
				addmult_end = false;
				scal += c;
			}
		}
		if (vec.size() > 0) {
			Tokens temp(vec);
			temp.type = Tokens::VECTOR;
			postfix_token.push_back(temp);
			vec = "";
		}
		if (scal.size() > 0) {
			Tokens temp(scal);
			temp.type = Tokens::SCALAR;
			postfix_token.push_back(temp);
			scal = "";
		}

		while (!operand_stack.empty()) {
			string toAdd = "";
			toAdd += operand_stack.top();
			Tokens temp(toAdd);
			temp.type = Tokens::OPERATOR;
			postfix_token.push_back(temp);
			operand_stack.pop();
		}

		string output = "";
		stack<Value> operands;
		for (auto p : postfix_token) {
			if (p.type == Tokens::VECTOR) {
				operands.push(Value(vects.find(p.token)->second));
			}
			else if (p.type == Tokens::SCALAR) {
				istringstream s(p.token); 
				double val;
				s >> val;
				operands.push(Value(val));
			}
			else {
				if (operands.size() < 2) {
					output = "INVALID";
					break;
				}
				Value op1 = operands.top();
				operands.pop();
				Value op2 = operands.top();
				operands.pop();
				Value resVal = EvalMe(op2, op1, p.token[0]);
				if (resVal.type == Value::Type::ERROR) {
					output = "INVALID";
					break;
				}
				else {
					operands.push(resVal);
				}
			}
		}

		if (output.size() == 0) {
			if (operands.size() > 1) {
				output = "INVALID";
			}
			else {
				stringstream ss;
				if (operands.top().type == Value::Type::VECTOR) {
					ss << operands.top().vec.x << " " << operands.top().vec.y;
					output = ss.str();
				}
				else {
					ss << to_string(operands.top().scal);
					output = ss.str();
				}
			}
		}
		cout << output << "\n";
	}

	return 0;
}