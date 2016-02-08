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

#endif