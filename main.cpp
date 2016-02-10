
//  Gian Salay 02/01/2016.

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <limits>

using namespace std;


class Vector2
{
public:
    string name;
    float x, y;
    Vector2(string name = "", float x = 0, float y = 0) :name(name), x(x),y(y) {}
    Vector2 operator+(const Vector2 &rhs)
    {
        return Vector2(name,x + rhs.x, y + rhs.y);
    }

    Vector2 operator-(const Vector2 &rhs)
    {
        return Vector2(name,x - rhs.x, y - rhs.y);
    }

    Vector2 operator*(const float s) const
    {
        return Vector2(name,x *s,y*s);
    }

    Vector2 operator/(const float s) const
    {
        return Vector2(name,x /s,y/s);
    }

    float operator*(const Vector2 &rhs) const{
        return x * rhs.x + y * rhs.y;
    }

    float operator%(const Vector2 &rhs) const{
        return x * rhs.y - y * rhs.x;
    }
};

struct Value{
    enum Type{VECTOR ,SCALAR} type;
    union{
        Vector2 v;
        double scalar;
    };
    Value(const Vector2 &v) : type(VECTOR), v(v){}
    Value(const double s) : type(SCALAR), scalar(s){}
    ~Value(){}
    Value(const Value& other){
        if(other.type == Type::SCALAR)
        {
           scalar = other.scalar;
        }
        else if (other.type == Type::VECTOR)
        {
            v = other.v;
        }
    }


};

bool isOperator( char x)
{
 if(x == '+' || x == '-' || x == '*' || x == '/' || x == '%')
    {
        return true;
    }
    else
    {
        return false;
    }
}


int opWeight(char op)
{
    int weight = 0;
    switch(op)
    {
        case '+':
            weight = 1;
            break;
        case '-':
            weight = 1;
            break;
        case '*':
            weight = 2;
            break;
        case '/':
            weight = 2;
            break;

        case '%':
            weight = 2;
            break;

    }
    return weight;
}

bool precedence(char op1, char op2)
{
    int op1Weight = opWeight(op1);
    int op2Weight = opWeight(op2);

    if(op1Weight == op2Weight)
    {
        return true;
    }
    else if (op1Weight < op2Weight){

        return false;
    }
    else{
        return true;
    }
    return false;
}

string intoPost(string infix)
{
    string postfix = "";
    stack<char> op_stack;
    for(int i = 0; i < infix.length(); i++)
    {
        if(infix[i] == ' ')
        {
            continue;
        }
        else if(isOperator(infix[i]))
        {

            while(!op_stack.empty() && op_stack.top() != '(' && precedence(op_stack.top(),infix[i]))
            {
                if(isdigit(postfix[postfix.length()]))
                {

                    postfix += " ";
                }
                postfix+= op_stack.top();
                postfix+= " ";
                op_stack.pop();

            }
            op_stack.push(infix[i]);


        }
        else if (infix[i] == '(')
        {
            op_stack.push(infix[i]);

        }

        else if(infix[i] == ')')
        {
            while(!op_stack.empty() && op_stack.top() !=  '(') {
                postfix += op_stack.top();
                postfix+= " ";

                op_stack.pop();

            }
            op_stack.pop();

        }
        else
        {

            postfix+= infix[i];
            if(infix[i+1] == ' ' || infix[i+1] == '\0' || infix[i+1] == '(' || infix[i+1] == ')'){
                postfix+= " ";
            }

        }
    }
    while(!op_stack.empty()) {
        postfix += op_stack.top();
        postfix+= " ";
        op_stack.pop();
    }
    cout<<postfix<<endl;
    return postfix;
}
string evaluate(string postfix,vector <Vector2>& vectorarray)
{
    stack<Value> valuestack;
    string current;
    stringstream stream(postfix);
    for(int i = 0; stream >> current; i++)
    {
       if(isOperator(current[0]))
       {

        Value a = valuestack.top();
         valuestack.pop();
         Value b = valuestack.top();
         valuestack.pop();
           switch(current[0])
           {
                case '+':
               {
                   if(a.type == a.Type::SCALAR && b.type == b.Type::SCALAR)
                   {
                        valuestack.push(a.scalar+b.scalar);
                   }
                   else if (a.type == a.Type::VECTOR && b.type == b.Type::VECTOR)
                   {
                       valuestack.push(a.v + b.v);
                   }
                   else
                   {
                       return "INVALID";
                   }
                   break;
               }
               case '-':
               {
                      if(a.type == a.Type::SCALAR && b.type == b.Type::SCALAR)
                   {
                        valuestack.push(a.scalar-b.scalar);
                   }
                   else if (a.type == a.Type::VECTOR && b.type == b.Type::VECTOR)
                   {
                       valuestack.push(a.v - b.v);
                   }
                   else
                   {
                       return "INVALID";
                   }
                   break;
               }
               case '*':
               {
                      if(a.type == a.Type::SCALAR && b.type == b.Type::SCALAR)
                   {
                        valuestack.push(a.scalar * b.scalar);
                   }
                   else if (a.type == a.Type::VECTOR && b.type == b.Type::VECTOR)
                   {

                       valuestack.push(a.v * b.v);
                   }

                   else if (a.type == a.Type::SCALAR && b.type == b.Type::VECTOR)
                   {
 

                       valuestack.push(b.v*a.scalar);
                   }
                   else
                   {
                       valuestack.push(b.v*a.scalar);
                   }
                   break;
               }
               case '/':
               {
                      if(a.type == a.Type::SCALAR && b.type == b.Type::SCALAR)
                   {
                        valuestack.push(a.scalar / b.scalar);
                   }
                   else if (a.type == a.Type::VECTOR && b.type == b.Type::VECTOR)
                   {

                       return "INVALID";
                   }

                   else if (a.type == a.Type::SCALAR && b.type == b.Type::VECTOR)
                   {


                       valuestack.push(b.v/a.scalar);
                   }
                   else
                   {
                       valuestack.push(b.v/a.scalar);
                   }
                   break;
               }
               case '%':
               {
                   if(a.type == a.Type::SCALAR && b.type == b.Type::SCALAR)
                   {
                        return "INVALID";
                   }
                   else if (a.type == a.Type::VECTOR && b.type == b.Type::VECTOR)
                   {

                       valuestack.push(a.v % b.v);
                   }

                   else if (a.type == a.Type::SCALAR && b.type == b.Type::VECTOR)
                   {
                        return "INVALID";
                   }
                   else
                   {
                        return "INVALID";
                   }
                   break;

               }

           }
       }
       else if(isalpha(current[0]))
       {
           for(int i = 0; i < vectorarray.size(); i++)
           {
               if(vectorarray.at(i).name == current)
               {
                   Vector2 vec = vectorarray.at(i);
                    Value vecval(vec);

                   valuestack.push(vecval);

               }
           }
       }
       else
       {
         Value val(stod(current,0));
         cout << "VAL: " << val.type << endl;
         valuestack.push(val);

       }
    }
     Value fin = valuestack.top();
     if(fin.type == fin.Type::SCALAR)
     {
         return to_string(fin.scalar);
     }
     else
     {
         return (to_string(fin.v.x) + " " + to_string(fin.v.y));
     }
}
int main(int argc, const char * argv[]) {
    string name;
    float x,y;
    vector <Vector2> vectors = {};
    while(cin.peek() != '=')
    {
        cin >> name >> x >> y;

        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        Vector2 vector (name,x,y);
        vectors.push_back(vector);
    }
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    while(true){
        string exp;
        getline(cin, exp);
        if (exp.empty())
        {
            break;
        }
        else{

           cout << evaluate(intoPost(exp),vectors);
        }
    }



    return 0;
}
