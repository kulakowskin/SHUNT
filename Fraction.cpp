#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
#include <stdlib.h>
#include "Fraction.h"

Fraction::Fraction(){
	this->numerator = 0;
	this->denominator = 0;
}
Fraction::Fraction(string frac_expression){
	if(frac_expression.find("/") == std::string::npos){
		frac_expression+="/1";
	}
	this->frac_c = strstr((char*)frac_expression.c_str(),frac_expression.c_str());
	this->parseNumbers();
	this->simplify();
}
Fraction::Fraction(int num, int den){
	this->numerator = num;
	this->denominator = den;
}
void Fraction::parseNumbers(){
	char* p;
  	p = strtok(frac_c,"(/)");
	this->numerator = atoi(p);
    p = strtok (NULL, " (/)");
    this->denominator = atoi(p);
}
int Fraction::getDenominator(){
	return this->denominator;
}
int Fraction::getNumerator(){
	return this->numerator;
}
Fraction& Fraction::operator*(Fraction& second){
	int n1 = this->getNumerator() * second.getNumerator();
    int d = this->getDenominator() * second.getDenominator();
    int gcd = this->gcd(n1,d);
	n1/=gcd;
	d/=gcd;
	Fraction* temp = new Fraction(n1,d);
	return *temp;
}
Fraction& Fraction::operator+(Fraction& second){
	int n1 = this->getNumerator() * second.getDenominator();
    int n2 = second.getNumerator() * this->getDenominator();
    int n = n1 + n2;
    int d = this->getDenominator() * second.getDenominator();
    int gcd = this->gcd(n,d);
	n/=gcd;
	d/=gcd;
	Fraction* temp = new Fraction(n,d);
	return *temp;
}
Fraction& Fraction::operator-(Fraction& second){
	int n1 = this->getNumerator() * second.getDenominator();
    int n2 = second.getNumerator() * this->getDenominator();
    int n = n1 - n2;
    int d = this->getDenominator() * second.getDenominator();
    int gcd = this->gcd(n,d);
	n/=gcd;
	d/=gcd;
	Fraction* temp = new Fraction(n,d);
	return *temp;
}
Fraction& Fraction::operator/(Fraction& second){
    int numer = (this->getNumerator() * second.getDenominator());
	int denom = (this->getDenominator() * second.getNumerator());
	int gcd = this->gcd(numer,denom);
	numer/=gcd;
	denom/=gcd;
	Fraction* temp = new Fraction(denom, numer);
    return *temp;
}
Fraction& Fraction::operator^(Fraction& p){
    int numer = pow(this->numerator, p.numerator);
	int denom = pow(this->denominator, p.numerator);
	int gcd = this->gcd(numer,denom);
	numer/=gcd;
	denom/=gcd;
	Fraction* temp = new Fraction(numer, denom);
    return *temp;
}
void Fraction::simplify(){
	int gcd = this->gcd(this->numerator,this->denominator);
	this->numerator = this->numerator/gcd;
	this->denominator = this->denominator/gcd;
}
string Fraction::toString(){
	stringstream ss;
	ss<<this->numerator;
	stringstream bb;
	bb<<this->denominator;
	return ss.str() + " / " + bb.str();
}
int Fraction::gcd(int a, int b){
	if((a%b)==0){
		return b;
	}
	else{
		return gcd(b, a%b);
	}
} 
