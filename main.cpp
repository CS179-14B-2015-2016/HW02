#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

struct Vector2f
{
	//float x;
	//float y;
	//string name;

public:
	string name;
	float x;
	float y;
	
	Vector2f()
	{
		name = "";
		x = 0;
		y = 0;
	}

	Vector2f(string nom, float a, float b)
	{
		name = nom;
		x = a;
		y = b;
	}

	//operator overloads
	Vector2f operator+(const Vector2f &rhs)
	{
		Vector2f ans;
		ans.x = this->x + rhs.x;
		ans.y = this->y + rhs.y;
		return ans;
	}
	Vector2f operator-(const Vector2f &rhs)
	{
		Vector2f ans;
		ans.x = this->x - rhs.x;
		ans.y = this->y - rhs.y;
		return ans;
	}
	Vector2f operator*(const float &rhs)
	{
		Vector2f ans;
		ans.x = this->x * rhs;
		ans.y = this->y * rhs;
		return ans;
	}
	Vector2f operator/(const float &rhs)
	{
		Vector2f ans;
		ans.x = this->x * (1/rhs);
		ans.y = this->y * (1 / rhs);
		return ans;
	}
	float operator*(const Vector2f &rhs)
	{
		//float ans;
		//ans = (this->x * rhs.x) + (this->y * rhs.y);
		//return ans;
		return (this->x * rhs.x) + (this->y * rhs.y);
	}
	float operator%(const Vector2f &rhs)
	{
		return (this->x * rhs.y) - (this->y * rhs.x);
	}
};
inline static Vector2f operator*(float lhs, Vector2f rhs)
{
	return rhs * lhs;
}


int main()
{
	
	bool declaring_vectors = true;
	vector<Vector2f> declared_vectors;
	string input_line;
	//stringstream line_splitter;
	string vector_name;
	float vector_x;
	float vector_y;
	
	while (!cin.fail())
	{
		getline(cin, input_line);
		//line_splitter.str("");

		//cout << input_line << endl;


		if (input_line == "=")
		{
			declaring_vectors = false;
		}

		if (declaring_vectors == true)
		{
			//line_splitter.str("");
			stringstream line_splitter;

			line_splitter << input_line;

			line_splitter >> vector_name;
			line_splitter >> vector_x;
			line_splitter >> vector_y;

			Vector2f vector_to_declare(vector_name, vector_x, vector_y);

			declared_vectors.push_back(vector_to_declare);

			/*
			cout << "vector name: " << declared_vectors.back().name << endl;
			cout << "vector x: " << declared_vectors.back().x << endl;
			cout << "vector y: " << declared_vectors.back().y << endl;
			cout << "number of vectors: " << declared_vectors.size() << endl;
			*/

			//cout << input_line << endl;
			//cout << "declaring vectors" << endl;
		}

		if (declaring_vectors == false)
		{
			//line_splitter.str("");
			bool left_scalar = true;
			bool right_scalar = true;
			float left_scalar_value;
			float right_scalar_value;
			string left_vector_name;
			Vector2f left_vector;
			string right_vector_name;
			Vector2f right_vector;
			string operation_operator;

			stringstream line_splitter;

			line_splitter << input_line;

			if (!(line_splitter >> left_scalar_value))
			{
				left_scalar = false;
				line_splitter >> left_vector_name;
				//loop through list of vector2f to find the right one
				vector<Vector2f>::iterator it;
				for (int i = 0; i < declared_vectors.size(); i++)
				{
					if (declared_vectors.at(i).name == left_vector_name)
					{
						left_vector = declared_vectors.at(i);
					}
				}
			}

			line_splitter >> operation_operator;

			if (!(line_splitter >> right_scalar_value))
			{
				right_scalar = false;
				line_splitter >> right_vector_name;
				//loop through list of vector2f to find the right one
				for (int i = 0; i < declared_vectors.size(); i++)
				{
					if (declared_vectors.at(i).name == right_vector_name)
					{
						right_vector = declared_vectors.at(i);
					}
				}
			}

			if ((left_scalar == true) && (right_scalar == true))
			{
				if (operation_operator == "+")
				{
					cout << (left_scalar_value + right_scalar_value) << endl;
				}
				else if (operation_operator == "-")
				{
					cout << (left_scalar_value - right_scalar_value) << endl;
				}
				else if (operation_operator == "*")
				{
					cout << (left_scalar_value * right_scalar_value) << endl;
				}
				else if (operation_operator == "/")
				{
					cout << (left_scalar_value / right_scalar_value) << endl;
				}
				else if (operation_operator == "%")
				{
					cout << "INVALID" << endl;
				}
			}
			else if ((left_scalar == false) && (right_scalar == true))
			{
				Vector2f resulting_vector;

				if ( (operation_operator == "+") || (operation_operator == "%") || (operation_operator == "-"))
				{
					cout << "INVALID" << endl;
				}
				else if (operation_operator == "*")
				{
					resulting_vector = left_vector * right_scalar_value;
					cout << resulting_vector.x << " " << resulting_vector.y << endl;
				}
				else if (operation_operator == "/")
				{
					resulting_vector = left_vector / right_scalar_value;
					cout << resulting_vector.x << " " << resulting_vector.y << endl;
				}
			}
			else if ((left_scalar == true) && (right_scalar == false))
			{
				Vector2f resulting_vector;

				if ((operation_operator == "+") || (operation_operator == "%") || (operation_operator == "-") || (operation_operator == "/"))
				{
					cout << "INVALID" << endl;
				}
				else if (operation_operator == "*")
				{
					resulting_vector = left_scalar_value * right_vector;
					cout << resulting_vector.x << " " << resulting_vector.y << endl;
				}
			}
			else if ((left_scalar == false) || (right_scalar == false))
			{
				Vector2f resulting_vector;

				if ((operation_operator == "/"))
				{
					cout << "INVALID" << endl;
				}
				if ((operation_operator == "+"))
				{
					resulting_vector = left_vector + right_vector;

					cout << resulting_vector.x << " " << resulting_vector.y << endl;
				}
				else if ((operation_operator == "-"))
				{
					resulting_vector = left_vector - right_vector;

					cout << resulting_vector.x << " " << resulting_vector.y << endl;
				}
				else if ((operation_operator == "*"))
				{
					cout << left_vector * right_vector;
				}
				else if ((operation_operator == "%"))
				{
					cout << left_vector % right_vector;
				}
			}


			//cout << input_line << endl;
			//cout << "declaring operations" << endl;
		}
	}
	


	//test for detecting end of file (success)
	/*
	string input;
	while (!cin.fail())
	{
		getline(cin, input);
		cout << input << endl;
	}
	*/

	//test for detecting end of file (success)
	/*
	string input;
	while (getline(cin, input))
	{
		cout << input << endl;
	}
	*/

	//test for detecting end of file (failed)
	/*
	string input;
	while (1)
	{
		getline(cin, input);
		cout << input << endl;
	}
	*/

	//overloaded operator tests
	/*
	Vector2f a(-5.4, 2.2);
	Vector2f b(12.5, -20.1);
	Vector2f ans;
	ans = a + b;
	cout << ans.x << " " << ans.y << "\n";
	cout << a * b << "\n";
	cout << a % b;
	*/

	cin.get();

	return 0;
}