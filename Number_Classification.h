#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include "Fraction.h"
#include "Sqrt.h"

using namespace std;
class Number_Classification{
	public:
		void enterExpression(char z);
		bool shunting_Yard();
		bool classify();
		bool is_number(const std::string& s);
		bool is_function(const std::string& s);
		bool is_operator(const std::string& s);
		bool is_sqrt(const std::string& s);
		bool is_rt(const std::string& s);
		bool is_log(const std::string& s);
		bool is_left(char op);
		int precedence(string s);
		void evalulate();
		void exptoToken();
		float operate(float num, string func);
		float operate(float n1, float n2, char z);
		void operate(vector<string>& stack, char z);
		string divide(stack<string>&stack);
		string add(stack<string>&stack);
		string subtract(stack<string>&stack);
		string exponent(stack<string>&stack);
		string multiply(stack<string>&stack);
		void replace_all(string& input, string& find, string& rep);
		string getPrevExp(int a);
	private:
		string expression;
		vector<string> expToken;
		vector<string> prevExpressions;
		queue<string> numbers;
		stack<string> operators;
		bool frac_float;
};
