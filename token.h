#ifndef token_h
#define token_h
#include "vector2.h"

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

token operate(const token& lhs, const token& rhs, const char op, bool* valid) {
	switch(op) {
		case '+':
			if(lhs.type==VECTOR && rhs.type==VECTOR)
				return token(lhs.v+rhs.v);
			else if(lhs.type==SCALAR && rhs.type==SCALAR)
				return token(lhs.f+rhs.f);
			else {
				*valid = false;
				return token();
			}
		case '-':
			if(lhs.type==VECTOR && rhs.type==VECTOR)
				return token(lhs.v-rhs.v);
			else if(lhs.type==SCALAR && rhs.type==SCALAR)
				return token(lhs.f-rhs.f);
			else {
				*valid = false;
				return token();
			}
		case '*':
			if(lhs.type==VECTOR && rhs.type==VECTOR)
				return token(lhs.v*rhs.v);
			else if(lhs.type==VECTOR && rhs.type==SCALAR)
				return token(lhs.v*rhs.f);
			else if(lhs.type==SCALAR && rhs.type==VECTOR)
				return token(lhs.f*rhs.v);
			else if(lhs.type==SCALAR && rhs.type==SCALAR)
				return token(lhs.f*rhs.f);
			else {
				*valid = false;
				return token();
			}
		case 's':
			if(lhs.type==VECTOR && rhs.type==SCALAR)
				return token(lhs.v*rhs.f);
			else if(lhs.type==SCALAR && rhs.type==VECTOR)
				return token(lhs.f*rhs.v);
			else if(lhs.type==SCALAR && rhs.type==SCALAR)
				return token(lhs.f*rhs.f);
			else {
				*valid = false;
				return token();
			}
		case '%':
			if(lhs.type==VECTOR && rhs.type==VECTOR)
				return token(lhs.v%rhs.v);
			else {
				*valid = false;
				return token();
			}
		case '/':
			if(lhs.type==VECTOR && rhs.type==SCALAR)
				return token(lhs.v/rhs.f);
			else if(lhs.type==SCALAR && rhs.type==SCALAR)
				return token(lhs.f/rhs.f);
			else {
				*valid = false;
				return token();
			}
	}
	return token();
}
#endif