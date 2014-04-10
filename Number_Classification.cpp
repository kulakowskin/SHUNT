#include <iostream>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include "Number_Classification.h"

#define PI 3.141592653589793
#define e 2.71828182846

using namespace std;
void Number_Classification::enterExpression(char z){
	z == 'y' || z == 'Y' ? this->frac_float = 1 : this->frac_float = 0;
	cout << "Enter Expression: " << endl;
	getline(cin, this->expression);
	this->exptoToken(z); 
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
bool Number_Classification::is_sqrt(const std::string& s){
	if (s.find("sqrt:") != std::string::npos) {
		return true;
	}
	return false;
}
bool Number_Classification::is_log(const std::string& s){
	if (s.find("log_") != std::string::npos) {
		return true;
	}
	return false;
}
bool Number_Classification::is_rt(const std::string& s){
	if (s.find("rt:") != std::string::npos) {
		return true;
	}
	return false;
}
string Number_Classification::getPrevExp(int a){
	if( a > this->prevExpressions.size()){
		return "Does not exist";
	}
	return this->prevExpressions.at(this->prevExpressions.size() - a);
}
void Number_Classification::replace_all(string& input, string& find, string& rep){
	size_t p = 0;
	while((p = input.find(find,p)) != std::string::npos){
		input.replace(p, find.length(), rep);
		p += rep.length();
	}
}
void Number_Classification::exptoToken(char z){
	shunt:
	string s;
    	if (this->expression.find(" ") == std::string::npos) {
        	if (!is_function(this->expression)) {
        	 cout<<"Please put a space between every input for system readibilty."<<endl;
		 }
    	}

	if(this->expression.find("ans") != std::string::npos && this->prevExpressions.size() == 0){
		cout << "\nNo Previous Answer(s). Re-enter an expression.\n" << endl;
		this->enterExpression('y');
		return;
	}
	if(this->expression.find("ans") != std::string::npos && this->prevExpressions.size() != 0){
		string ans = "ans";
		replace_all(this->expression, ans, this->prevExpressions.back());
	}
	stringstream p(this->expression);
	string t;
	char* q;
	while(getline(p,t,' ')){
		this->expToken.push_back(t);
	}
	bool passed = false;
	
	for(int i=0; i < expToken.size(); i++){
		if(is_function(expToken.at(i))){
			if(is_sqrt(expToken.at(i))){
				Sqrt q(expToken.at(i));
				expToken.at(i) = q.simRoots();
				passed = true;
			}
			/*if(is_log()){
				
			}
			if(is_rt()){
				
			}*/
		}
		if(expToken.at(i).compare("pi") == 0){
				expToken.at(i) = "pi";
				passed = true;
		}
		if(expToken.at(i).compare("e") == 0){
				expToken.at(i) = "e";
				passed = true;
		}
	}
	if(passed == true && (z == 'Y' || z == 'y')){
		string t;
		cout << "\n";
		for(int i=0; i < expToken.size(); i++){
			t+=expToken.at(i) + " ";
		}
		prevExpressions.push_back("( "+ t +" )");
		expressions_b.push_back(this->expression);
		cout << "\n\n";
		if(!is_function(t) &&  t.find("e") == std::string::npos && t.find("pi") == std::string::npos){
			this->expression = t;
			expToken.clear();
			goto shunt;
		}
		cout << t << endl;
		expToken.clear();
		return;
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
	stack<float> decimal_eval;
	string o;
    while(!numbers.empty()){
        o = numbers.front();
		numbers.pop();
		if(is_number(o)){
			eval.push(o);
			decimal_eval.push(atof(o.c_str()));
		}
		/*else if(is_function(o)){
			
		}*/
		else{
			if(decimal_eval.size() > 1){
				float t1 = decimal_eval.top();
				decimal_eval.pop();
				float t2 = decimal_eval.top();
				decimal_eval.pop();
				decimal_eval.push(operate(t2,t1, o[0]));
			}
			switch(o[0]){
				case '*':
					multiply(eval);
					break;
				case '/':
					divide(eval);
					break;
				case '+':
					add(eval);
					break;
				case '-':
					subtract(eval);
					break;
				/*case 's':
					eval.push(o);
					square_root(eval);
					break;*/
				case '^':
					exponent(eval);
					break;
			}
    	}
    }
    if(this->frac_float == 1){
		cout << "\n" << eval.top() << " - Fractional\n" << endl;
		prevExpressions.push_back("( "+eval.top()+" )");		
    }
    if(this->frac_float == 0){
    	cout << "\n" << decimal_eval.top() << " - Float Representation\n" << endl;
    	stringstream ss;
    	ss << decimal_eval.top();
    	prevExpressions.push_back("( "+ss.str()+" )");
    }
    expressions_b.push_back(this->expression);
    expToken.clear();
}
void Number_Classification::writeFile(){
	ofstream myfile;
	myfile.open("Previous_Expressions.txt");
	cout << "\n\nSaving evaluated expressions to text file...\n" << endl;
	for(int i=0;i<prevExpressions.size();i++){
		myfile << expressions_b.at(i) + " = " + prevExpressions.at(i) + '\n';	
	}
	cout << "Saved.\n\n" << endl;
  	myfile.close();
}
string Number_Classification::square_root(stack<string>& stack){
	Sqrt t(stack.top());
	stack.pop();
	stack.push(t.simRoots());
	cout << t.simRoots() << endl;
	return t.simRoots();
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
			cout << "MisMatched Paranthesis\n" << endl;
			return false;
		}
		this->numbers.push(this->operators.top());
		this->operators.pop();
	}
	this->evalulate();
	return true;
}
