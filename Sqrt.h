#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Sqrt{
	public:
		Sqrt();
		Sqrt(string expression);
		string simRoots();
		void parseNumbers();
	private: 
		int multiplier;    //multiplier
		int radicand;   //radicand
		int factor_c; //factor count
		int mf; //largest factor
		float in;
		char* expression;
		
};
