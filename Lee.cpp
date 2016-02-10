#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Vector2 {
	public:
		string name;
		double x, y;
		Vector2(string name = "", double x = 0, double y = 0) : name(name), x(x), y(y) {};
		friend istream& operator>> (istream &in, Vector2 &v);
		friend ostream& operator<< (ostream &out, const Vector2 &v);
};

class Operand {
	public:
		Vector2 v;
		double s;
		enum {NONE, SCALAR, VECTOR} type;
		Operand() : type(Operand::NONE) {}
		friend stringstream& operator>> (stringstream &in, Operand &op);
		friend ostream& operator<< (ostream &out, const Operand &op);
		friend Operand operator+ (const Operand &lhs, const Operand &rhs);
};

class Equation {
	public:
		Operand lhs;
		void evaluate(const char &operation, Operand &lhs, const Operand &rhs);
		friend istream& operator>> (istream &in, Equation &eq);
		friend ostream& operator<< (ostream &out, const Equation &eq);
};

vector<Vector2> v2;

int main() {
	while (1) {
		while (1) {
			Vector2 v;
			cin >> v;
			if (cin.fail()) cin.clear();
			else if (cin.eof()) {
				cin.clear();
				break;
			}
			else v2.push_back(v);
		}
		while (1) {
			Equation e;
			cin >> e;
			if (cin.fail()) cin.clear();
			else cout << e.lhs << '\n';
		}
	}
}

istream& operator>> (istream &in, Vector2 &v) {
	string s = "";
	getline(in, s);
	if (s == "=") {
		in.setstate(ios_base::eofbit);
		return in;
	}
	
	bool isValidVector = true;
	enum{NAME, X, Y} state;
	state = NAME;
	stringstream current;
	
	for (int i = 0; i < s.length() && isValidVector; ++i) {
		switch (state) {
			case NAME:
			if (isspace(s[i]) && current.str() != "") {
				current >> v.name;
				for (int j = 0; j < v2.size(); ++j) {
					if (v.name == v2[j].name) {
						isValidVector = false;
						break;
					}
				}
				state = X;
				current.str("");
				current.clear();
			} else {
				current << s[i];
				if (!isalpha(s[i])) isValidVector = false;
			}
			break;
			case X:
			if (isspace(s[i]) && current.str() != "") {
				current >> v.x;
				if (current.fail()) isValidVector = false;
				state = Y;	
				current.str("");
				current.clear();
			} else {
				current << s[i];
				if (isalpha(s[i]) || isspace(s[i])) isValidVector = false;
			}
			break;
			case Y:
			current << s[i];
			if (isalpha(s[i]) || isspace(s[i])) isValidVector = false;
			if (i+1 == s.length() && current.str() != "") {
				current >> v.y;
				if (current.fail()) isValidVector = false;
				current.str("");
				current.clear();
			}
			break;
		}
	}
	if (!isValidVector || state != Y) {
		delete &v;
		in.setstate(ios_base::failbit);
		cout << "invalid vector" << '\n';
	}
	return in;
}

ostream& operator<< (ostream &out, const Vector2 &v) {
	out << v.x << " " << v.y;
	return out;
}

stringstream& operator>> (stringstream &in, Operand &op) {
	in >> op.s;
	bool isScalar = !in.fail();
	string s = in.str();
	in.ignore(s.length());
	isScalar = isScalar && (in.gcount() == 0);
	if (isScalar) {
		op.type = Operand::SCALAR;
		in.str("");
		in.clear();
		return in;
	} else {
		for (int i = 0; i < v2.size(); ++i) {
			if (s == v2[i].name) {
				op.v = v2[i];
				op.type = Operand::VECTOR;
				in.str("");
				in.clear();
				return in;
			}
		}
	}
	return in;
}

ostream& operator<< (ostream &out, const Operand &op) {
	switch (op.type) {
		case Operand::VECTOR:
		cout << op.v;
		break;
		case Operand::SCALAR:
		cout << op.s;
		break;
	}
	return out;
}

Operand operator+ (const Operand &lhs, const Operand &rhs) {
	Operand s;
	if (lhs.type == Operand::VECTOR && rhs.type == Operand::VECTOR) {
		s.type = Operand::VECTOR;
		Vector2 v("", lhs.v.x+rhs.v.x, lhs.v.y+rhs.v.y);
		s.v = v;
	} else if (lhs.type == Operand::SCALAR && rhs.type == Operand::SCALAR) {
		s.type = Operand::SCALAR;
		s.s = lhs.s+rhs.s;
	}
	return s;
}

Operand operator- (const Operand &lhs, const Operand &rhs) {
	Operand s;
	if (lhs.type == Operand::VECTOR && rhs.type == Operand::VECTOR) {
		s.type = Operand::VECTOR;
		Vector2 v("", lhs.v.x-rhs.v.x, lhs.v.y-rhs.v.y);
		s.v = v;
	} else if (lhs.type == Operand::SCALAR && rhs.type == Operand::SCALAR) {
		s.type = Operand::SCALAR;
		s.s = lhs.s-rhs.s;
	}
	return s;
}

Operand operator* (const Operand &lhs, const Operand &rhs) {
	Operand s;
	if (lhs.type == Operand::VECTOR && rhs.type == Operand::VECTOR) {
		s.type = Operand::SCALAR;
		s.s = (lhs.v.x*rhs.v.x)+(lhs.v.y*rhs.v.y);
		
	} else if (lhs.type == Operand::SCALAR && rhs.type == Operand::VECTOR) {
		s.type = Operand::VECTOR;
		Vector2 v("", lhs.s*rhs.v.x, lhs.s*rhs.v.y);
		s.v = v;
	} else if (lhs.type == Operand::VECTOR && rhs.type == Operand::SCALAR) {
		s.type = Operand::VECTOR;
		Vector2 v("", rhs.s*lhs.v.x, rhs.s*lhs.v.y);
		s.v = v;
	} else if (lhs.type == Operand::SCALAR && rhs.type == Operand::SCALAR) {
		s.type = Operand::SCALAR;
		s.s = lhs.s*rhs.s;
	}
	return s;
}

Operand operator/ (const Operand &lhs, const Operand &rhs) {
	Operand s;
	if (lhs.type == Operand::VECTOR && rhs.type == Operand::VECTOR) {
		s.type = Operand::SCALAR;
		s.s = (lhs.v.x/rhs.v.x)+(lhs.v.y/rhs.v.y);
		
	} else if (lhs.type == Operand::VECTOR && rhs.type == Operand::SCALAR) {
		s.type = Operand::VECTOR;
		Vector2 v("", lhs.v.x/rhs.s, lhs.v.y/rhs.s);
		s.v = v;
	} else if (lhs.type == Operand::SCALAR && rhs.type == Operand::SCALAR) {
		s.type = Operand::SCALAR;
		s.s = lhs.s/rhs.s;
	}
	return s;
}

Operand operator% (const Operand &lhs, const Operand &rhs) {
	Operand s;
	if (lhs.type == Operand::VECTOR && rhs.type == Operand::VECTOR) {
		s.type = Operand::SCALAR;
		s.s = (lhs.v.x*rhs.v.y)-(lhs.v.y*rhs.v.x);
	}
	return s;
}

istream& operator>> (istream &in, Equation &eq) {
	string s = "";
	getline(in, s);
	
	string operations = "+-*/%";
	
	bool isValidEquation = true;
	stringstream current;
	Operand rhs;
	char operation = ' ';
	
	for (int i = 0; i < s.length() && isValidEquation; ++i) {
		if (operations.find(s[i]) != string::npos) {
			operation = s[i];
		} else if (!isspace(s[i])) {
			current << s[i];
			if (i+1 == s.length()) {
				if (operation == ' ') current >> eq.lhs;
				else {
					current >> rhs;
					eq.evaluate(operation, eq.lhs, rhs);
				}
				if (current.fail()) isValidEquation = false;
			} else if (isspace(s[i+1]) || operations.find(s[i+1]) != string::npos) {
				if (operation == ' ') current >> eq.lhs;
				else {
					current >> rhs;
					eq.evaluate(operation, eq.lhs, rhs);
				}
				if (current.fail()) isValidEquation = false;
			}
		}
	}
	if (!isValidEquation || eq.lhs.type == Operand::NONE) {
		in.setstate(ios_base::failbit);
		cout << "invalid equation" << '\n';
	}
	return in;
}

void Equation::evaluate(const char &operation, Operand &lhs, const Operand &rhs) {
	switch (operation) {
		case '+':
		lhs = lhs+rhs;
		break;
		case '-':
		lhs = lhs-rhs;
		break;
		case '*':
		lhs = lhs*rhs;
		break;
		case '/':
		lhs = lhs/rhs;
		break;
		case '%':
		lhs = lhs%rhs;
		break;
		default:
		Operand o;
		lhs = o;
		break;
	}
}