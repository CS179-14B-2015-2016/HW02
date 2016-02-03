
//  Gian Salay 02/01/2016.

#include <iostream>
#include <vector>
#include<stack>

using namespace std;
class Vector2
{
public:
    char name;
    float x, y;
    Vector2(char name = ' ', float x = 0, float y = 0) :name(name), x(x),y(y) {}
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
           // cout << op_stack.top() << endl;
            while(!op_stack.empty() && op_stack.top() != '(' && precedence(op_stack.top(),infix[i]))
            {
                postfix+= op_stack.top();
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
                op_stack.pop();
                
            }
            op_stack.pop();
            
        }
        else
        {
            postfix+= infix[i];
            
        }
    }
    while(!op_stack.empty()) {
        postfix += op_stack.top();
        op_stack.pop();
    }
    return postfix;
}

string evaluate(string postfix,vector <Vector2>& vector)
{
    stack<char> stack;
    string final;
    for(int i = 0; i < postfix.length();i++)
    {
        if(isOperator(postfix[i]))
        {
           switch(postfix[i])
            {
                case '+':
                {
                    char op1 = stack.top();
                    stack.pop();
                    char op2 = stack.top();
                    stack.pop();
                    if(isalpha(op1) && isalpha(op2))
                    {
                        Vector2 vec1, vec2;
                        for(int i = 0; i < vector.size(); i++)
                        {
                            if(vector.at(i).name == op1)
                            {
                                vec1 = vector.at(i);
                                vector.erase(vector.begin() + i);
                                                            }
                            else if( vector.at(i).name == op2)
                            {
                                vec2 = vector.at(i);
                                vector.erase(vector.begin() + i);
                               
                            }
                        }
                        vec1 = vec1 + vec2;
                        vector.push_back(vec1);
                        cout<< vec1.name;
                        stack.push(vec1.name);
                        break;
                    }
                    else if((!isalpha(op1) && isalpha(op2)) ||(!isalpha(op1) && isalpha(op2)))
                    {
                        return "INVALID";
                    }
                    else
                    {
                        
                        float x = op1;
                        float y = op2;
                        float result = (x + y);
                        stack.push(result);
                        break;
                    }
                }
                case '-':
                {
                 
                    char op1 = stack.top();
                    stack.pop();
                    char op2 = stack.top();
                    stack.pop();
                    if(isalpha(op1) && isalpha(op2))
                    {
                        Vector2 vec1, vec2;
                        for(int i = 0; i < vector.size(); i++)
                        {
                            if(vector.at(i).name == op1)
                            {
                                vec1 = vector.at(i);
                                vector.erase(vector.begin() + i);
                            }
                            else if( vector.at(i).name == op2)
                            {
                                vec2 = vector.at(i);
                                vector.erase(vector.begin() + i);
                                
                            }
                            
                        }
                        vec1 = vec1 - vec2;
                        vector.push_back(vec1);
                        stack.push(vec1.name);
                         break;
                    }
                    else if((!isalpha(op1) && isalpha(op2)) ||(!isalpha(op1) && isalpha(op2)))
                    {
                        return "INVALID";
                    }
                    else
                    {
                        float x = op1;
                        float y = op2;
                        float result = x - y;
                        //cout<< "result"<<result<<endl;
                        stack.push(result);
                         break;
                    }
                }
                case '/':
                {
                    char op1 = stack.top();
                    stack.pop();
                    char op2 = stack.top();
                    stack.pop();
                    if(isalpha(op1) && isalpha(op2))
                    {
                        return "INVALID";
                    }
                    else if(isalpha(op1) && !isalpha(op2))
                    {
                        
                        Vector2 vec1;
                        for(int i = 0; i < vector.size(); i++)
                        {
                            if(vector.at(i).name == op1)
                            {
                                vec1 = vector.at(i);
                                vector.erase(vector.begin() + i);
                            }
                        }
                        float y = op2;
                        vec1 = vec1 / y;
                        vector.push_back(vec1);
                        stack.push(vec1.name);
                         break;
                    }
                    else if (!isalpha(op1) && isalpha(op2))
                    {
                        return "INVALID";
                    }
                    else
                    {
                        float x = op1;
                        float y = op2;
                        float result = (x / y);
                        stack.push(result);
                         break;
                    }
                }
                case '*':
                {
                    char op1 = stack.top();
                    stack.pop();
                    char op2 = stack.top();
                    stack.pop();
                    if(isalpha(op1) && isalpha(op2))
                    {
                        Vector2 vec1, vec2;
                        for(int i = 0; i < vector.size(); i++)
                        {
                            if(vector.at(i).name == op1)
                            {
                                vec1 = vector.at(i);
                                vector.erase(vector.begin() + i);
                            }
                            else if( vector.at(i).name == op2)
                            {
                                vec2 = vector.at(i);
                                vector.erase(vector.begin() + i);
                                
                            }
                            
                        }
                        float result = (vec1 * vec2);
                        stack.push(result);
                         break;
                    }
                    else if((!isalpha(op1) && isalpha(op2)) ||(!isalpha(op1) && isalpha(op2)))
                    {
                        return "INVALID";
                    }
                    else
                    {
                        float x = op1;
                        float y = op2;
                        float result =(x * y); 
                        
                        stack.push(result);
                         break;
                    }
                }
                case '%':
                {
                    char op1 = stack.top();
                    stack.pop();
                    char op2 = stack.top();
                    stack.pop();
                    if(isalpha(op1) && isalpha(op2))
                    {
                        Vector2 vec1, vec2;
                        for(int i = 0; i < vector.size(); i++)
                        {
                            if(vector.at(i).name == op1)
                            {
                                vec1 = vector.at(i);
                                vector.erase(vector.begin() + i);
                            }
                            else if( vector.at(i).name == op2)
                            {
                                vec2 = vector.at(i);
                                vector.erase(vector.begin() + i);
                                
                            }
                            
                        }
                        vec1 = vec1 + vec2;
                        vector.push_back(vec1);
                        stack.push(vec1.name);
                         break;
                    }
                    else
                    {
                       return "INVALID";
                    }
                }
            }
            
            //stack_push(result);

        }
        else{
          
            stack.push(postfix[i]);
        }
            
    }
    while(!stack.empty()) {
        
        if(isalpha(stack.top()))
        {
            Vector2 y = stack.top();
            for(Vector2 x: vector)
            {
                
                if(x.name == y.name )
                {
                    
                    final += x.x;
                    final += " ";
                    final += x.y;
                }
            }
        }
        else{
        final += stack.top();
        }
        stack.pop();
    }

    return final;
};

int main(int argc, const char * argv[]) {
    char name;
    float x,y;
    vector <Vector2> vectors = {};
    while(cin.peek() != '=')
    {
        cin >> name >> x >> y;
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Vector2 vector (name,x,y);
        vectors.push_back(vector);
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(true)
    {
        string exp;
        getline(cin, exp);
        if (exp.empty())
        {
            break;
        }
        else{
          
           cout<<evaluate(intoPost(exp), vectors)<<endl;
        }
    }

  
    
    return 0;
}
