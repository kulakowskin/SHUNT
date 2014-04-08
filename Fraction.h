#include <string>
using namespace std;
class Fraction{
	public:
		Fraction();
		Fraction(string frac_expression);
		Fraction(int num, int den);
		void parseNumbers();
		void simplify();
		string toString();
		int gcd(int a, int b);
		int getNumerator();
		int getDenominator();
		Fraction& operator/(Fraction& second);
		Fraction& operator+(Fraction& second);
		Fraction& operator-(Fraction& second);
		Fraction& operator^(Fraction& p);
		Fraction& operator*(Fraction& p);
	private:
		int numerator;
		int denominator;
		char* frac_c;
		
};
