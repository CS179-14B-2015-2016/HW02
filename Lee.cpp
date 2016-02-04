#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

class vector2 {
	private:
		string name;
		int x, y;
		
	public:
		vector2(string name = "", int x = 0, int y = 0) : name(name), x(x), y(y) {};
		string getName() { return name; };
		friend istream& operator>> (istream &in, vector2 &v);
		friend ostream& operator<< (ostream &out, const vector2 &v);
		vector2 operator+ (vector2 &v) {
			vector2 a(name+"+"+v.name, x+v.x, y+v.y);
			cout << a << '\n';
			return a;
		};
};

istream& operator>> (istream &in, vector2 &v) {
	in >> v.name;
	if (v.name == "=" && in.peek() == '\n') {
		in.setstate(ios_base::eofbit);
		return in;
	}
	for (int i = 0; i < v.name.length(); ++i) {
		if (isdigit(v.name[i]) || ispunct(v.name[i])) {
			in.setstate(ios_base::failbit);
			return in;
		}
	}
	in >> v.x;
	in >> v.y;
	return in;
}

ostream& operator<< (ostream &out, const vector2 &v) {
	out << v.name << " " << v.x << " " << v.y;
	return out;
}

class equation {
	private:
		vector2 op1, op2;
		char opr;
		
	public:
		equation() {};
		friend istream& operator>> (istream &in, equation &eq);
		friend ostream& operator<< (ostream &out, const equation &eq);
};

vector<vector2> v2;

istream& operator>> (istream &in, equation &eq) {
	string opd = "";
	in >> opd;
	for (int i = 0; i < v2.size(); ++i) {
		if (v2.at(i).getName() == opd) eq.op1 = v2.at(i);
	}
	in >> eq.opr;
	in >> opd;
	for (int i = 0; i < v2.size(); ++i) {
		if (v2.at(i).getName() == opd) eq.op2 = v2.at(i);
	}
	switch (eq.opr) {
		case '+':
			eq.op1+eq.op2;
			break;
		/*case '*':
			eq.op1*eq.op2;
			break;
		case '/':
			eq.op1/eq.op2;
			break;
		case '-':
			eq.op1-eq.op2;
			break;*/
	}
}

int main() {
	while (1) {
		while (1) {
			vector2 v;
			cin >> v;
			if (cin.fail()) {
				cout << "invalid vector" << '\n';
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (cin.eof()) {
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			else v2.push_back(v);
		}
		while (1) {
			equation e;
			cin >> e;
		}
	}
}