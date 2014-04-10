#include <string>
#include "Number_Classification.h"
class Menu:public Number_Classification{
	public:
		bool printMenu();
		void printMenu_basic();
	private:
		bool readChoice();
		char frac_float;
		std::string userinput;
};
