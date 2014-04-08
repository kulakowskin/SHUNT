#include <iostream>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <sstream>
#include "Number_Classification.h"
using namespace std;
void Number_Classification::enterExpression(){
	cout << "Enter Expression: " << endl;
	getline(cin, this->expression);
	this->exptoToken(); 
}
bool Number_Classification::is_number(const std::string& s){
    std::string nu = s;
    int number = 0;
    std::stringstream m(nu);
    if (m >> number){
        return true;
    }
    else{
        return false;
    }
}
int Number_Classification::precedence(string s){
	switch(s.c_str()[0]){
		case '^':
			return 2;
		case '*':
		case '/':
			return 1;
		case '+':
		case '-':
			return 0;
		default:
			return -1;
	}
}

bool Number_Classification::is_operator(const std::string& s){
	if(s.compare("+") == 0 || s.compare("-") == 0 ||
	   s.compare("*") == 0 || s.compare("/") == 0 || 
	   s.compare("^") == 0 || s.compare(")") == 0 || 
	   s.compare("(") == 0){
		return true;
	}
	return false;
}
bool Number_Classification::is_function(const std::string& s){
	if (s.find("sqrt:") != std::string::npos) {
		return true;
	}
	if (s.find("rt:") != std::string::npos) {
		return true;
	}
	if (s.find("log_") != std::string::npos) {
		return true;
	}
	return false;
}
void Number_Classification::exptoToken(){
	stringstream p(this->expression);
	string t;
	char* q;
	while(getline(p,t,' ')){
		this->expToken.push_back(t);
	}
	this->shunting_Yard();
}
bool Number_Classification::is_left(char op){
	switch(op){
    	case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
    }
}
void Number_Classification::evalulate(){
	stack<string> eval;
    while(!numbers.empty()){
        string o = numbers.front();
		numbers.pop();
		if(is_number(o)){
			eval.push(o);
		}
		else if(is_function(o)){
			//string numb = eval.top();
			//eval.pop();
			//string result = operate(numb, o);
			//eval.push(result);
		}
		else{
			switch(o[0]){
				case '*':
					multiply(eval);
					break;
				case '/':;
					divide(eval);
					break;
				case '+':;
					add(eval);
					break;
				case '-':;
					subtract(eval);
					break;
				case '^':;
					exponent(eval);
					break;
			}
    	}
    }
    cout << "\n" << eval.top() << "\n\n" << endl;
}
string Number_Classification::multiply(stack<string>& stack){
	Fraction t1(stack.top());
	stack.pop();
	Fraction t2(stack.top());
	stack.pop();
	Fraction t3 = t1*t2;
	stack.push(t3.toString());
	return t3.toString();
}
string Number_Classification::divide(stack<string>& stack){
	Fraction t1(stack.top());
	stack.pop();
	Fraction t2(stack.top());
	stack.pop();
	Fraction t3 = t1/t2;
	stack.push(t3.toString());
	return t3.toString();
}
string Number_Classification::add(stack<string>& stack){
	Fraction t1(stack.top());
	stack.pop();
	Fraction t2(stack.top());
	stack.pop();
	Fraction t3 = t1+t2;
	stack.push(t3.toString());
	return t3.toString();
}
string Number_Classification::subtract(stack<string>& stack){
	Fraction t1(stack.top());
	stack.pop();
	Fraction t2(stack.top());
	stack.pop();
	Fraction t3 = t2-t1;
	stack.push(t3.toString());
	return t3.toString();
}
string Number_Classification::exponent(stack<string>& stack){
	Fraction t1(stack.top());
	stack.pop();
	Fraction t2(stack.top());
	stack.pop();
	Fraction t3 = t2^t1;
	stack.push(t3.toString());
	return t3.toString();
}
float Number_Classification::operate(float num, string func){
    	/*if(func == "sin")
    		return sin(num);
    	else if(func == "cos")
    		return cos(num);
    	else if(func == "log")
    		return log10(num);  */  	
    	return 0;
}
float Number_Classification::operate(float n1, float n2, char z){
	switch(z)
		{
    		case '+':
    			return n1 + n2;
    		case '-':
    			return n1 - n2;
    		case '*':
    			return n1 * n2;
    		case '/':
    			return n1 / n2;
    		case '^':
    			return pow(n1, n2);
    		default:
    			return 0;
    	}
}
bool Number_Classification::shunting_Yard(){
	for(int i=0;i<this->expToken.size();i++){
		if(is_number(this->expToken.at(i))){
			this->numbers.push(this->expToken.at(i));	
		}
		else if(is_function(this->expToken.at(i)) && !is_operator(this->expToken.at(i))){
			this->operators.push(this->expToken.at(i));		
		}
		else{
			bool left = is_left(this->expToken.at(i)[0]);
			int prec = this->precedence(this->expToken.at(i));
			if(expToken.at(i) != "(" && expToken.at(i) != ")"){
				// ENCASED OR IN OWN PARANTHESIS
				while(!this->operators.empty() && (( left && prec <= this->precedence(this->operators.top())) || (!left && prec < this->precedence(this->operators.top())))){
					this->numbers.push(this->operators.top());
					this->operators.pop();
				}
				this->operators.push(this->expToken.at(i));		
			}
			if(this->operators.size() == 0 || this->expToken.at(i).compare("(") == 0){
				this->operators.push(this->expToken.at(i));	
			}
			if(this->expToken.at(i).compare(")") == 0){
				while(this->operators.top().compare("(") != 0){
					this->numbers.push(operators.top());
			  		this->operators.pop();
				}
				if(this->operators.top().compare("(") == 0){
					operators.pop();
				}
				if(!operators.empty() && is_function(this->operators.top())){
					this->numbers.push(this->operators.top());
					this->operators.pop();		
				}
			}
		}	
	}
	while(!this->operators.empty()){
		if(this->operators.top().compare("(") == 0 || this->operators.top().compare(")") == 0 ){
			cout << "MisMatched Paranthesis!" << endl;
			return false;
		}
		this->numbers.push(this->operators.top());
		this->operators.pop();
	}
	this->evalulate();
	return true;
}
