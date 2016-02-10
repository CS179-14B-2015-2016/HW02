#include <iostream>


Vector::Vector():x(0),y(0){
	//cout<<"This Is A Default Constructor.";
}

Vector Vector::operator +(const Vector &v)const{  //Addition
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

Vector Vector::operator -(const Vector &v)const { //Subtraction
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}

Vector Vector::operator *(const int k)const{  //Multiplication By Scalar
	Vector res;
	res.x = k * x;
	res.y = k * y;
	return res;
}

void Vector::GetData(){			//Input The Vector
	cout<<"Enter The Value Of a : ";
	cin>>a;
	a = x;
	cout<<"Enter The Value Of b : ";
	cin>>b;
	b = y;
}

Vector operator *(int k,const Vector &v){
	return v * k;
}



Vector Vector::operator *(const Vector &v)const{ //Cross (or Vector) Product
	Vector res;
	res.x = (y * v.z) - (z * v.y);
	res.y = (z * v.x) - (x * v.z);
	return res;
}

void Vector::DotProd(Vector v2){    //Dot(Or Scalar) Product
	int v1v2;
	v1v2 = (x * v2.x)+(y * v2.y);
	cout<<"The Value Of A.B Is: "<<v1v2;
}

ostream & Vector::Show(ostream & out)const{
	if((x<0) && (y<0) && (z<0))
	out<<x<<"I"<<y<<"J"<<z<<"K";

	if((x<0) && (y<0) && (z>=0))
	out<<x<<"I"<<y<<"J+"<<z<<"K";

	if((x<0) && (y>=0) && (z<0))
	out<<x<<"I+"<<y<<"J"<<z<<"K";

	if((x<0) && (y>=0) && (z>=0))
	out<<x<<"I+"<<y<<"J+"<<z<<"K";

	if((x>=0) && (y<0) && (z<0))
	out<<x<<"I"<<y<<"J"<<z<<"K";

	if((x>=0) && (y<0) && (z>=0))
	out<<x<<"I"<<y<<"J+"<<z<<"K";

	if((x>=0) && (y>=0) && (z<0))
	out<<x<<"I+"<<y<<"J"<<z<<"K";

	if((x>=0) && (y>=0) && (z>=0))
	out<<x<<"I+"<<y<<"J+"<<z<<"K";

	return out;
}
