#include <iostream>
#include "Menu.h"
using namespace std;


bool Menu::printMenu(){
	cout << "1.) Compute new expression" << endl;
	cout << "2.) Help" << endl;
	cout << "3.) Review previous expression and answers" << endl;
	cout << "4.) Quit" << "\n" << endl;
	bool choice = this->readChoice();
	return choice == true ? true : false;
}
void Menu::printMenu_basic(){
	cout << "Welcome to MathWorks.\n\n\n";
}
bool Menu::readChoice(){
	read:
	string input;
	cin >> input;
	cin.ignore();
	cout << endl;
	if(input.compare("back") != 0 && input.compare("Back") != 0 && 
	   input.compare("quit") != 0 && input.compare("Quit") != 0 && 
	   input.compare("1") != 0 && input.compare("2") != 0 &&
	   input.compare("3") != 0 && input.compare("4") != 0){
	   	cout << "Invalid Input. Please Try again.\n" << endl;
	   	goto read;
	   }
	if(input.compare("1") == 0){
		//call function to take in user expression
		this->enterExpression();
	}
	else if(input.compare("2") == 0){
		//enter program dialog mode that details how to specify math operations
		helpMenu:
                //enter program dialog mode that details how to specify math operations
                cout<<"Welcome to the help menu!\n"<<endl;
                cout<<"\t1.)Display input syntax expectations"<<endl;
                cout<<"\t2.)Sample input"<<endl;
                cout<<"\t3.)Go back to main menu\n"<<endl;
                cout<<"Please enter your selection with your keypad"<<endl;
                
                char helpInput;
                cin >> helpInput;
                cout << '\n';
				
                if(helpInput != '1' && helpInput != '2' && helpInput != '3'){
                        cout<<"INVALID input. Please Try again. \n "<<endl;
                        goto helpMenu;
                }
                if(helpInput == '1'){
                        cout<<"1.)Power: "<<endl;
                        cout<<"\t x to the power of y == X^Y"<<endl;
                        cout<<"\t Example: 2^3\n"<<endl;
                        cout<<"2.)Square Roots: "<<endl;
                        cout<<"\t The square root of x == sqrt:x"<<endl ; 
                        cout<<"\t Example: sqrt:5\n"<<endl;
                        cout<<"3.)nth root: "<<endl;
                        cout<<"\t the nth root of x == nrt:x "<<endl; 
                        cout<<"\t Example: 5rt:5\n"<<endl;
                        cout<<"4.) Logs: "<<endl;
                        cout<<"\t log base b of x == log_b:x "<<endl; 
                        cout<<"\t Example: log_2:5\n"<<endl;
                }
                else if(helpInput == '2'){
                        cout<<"Sample user Input: "<<endl;
                        cout<<"\t  3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3 + log_2:8 \n"<<endl;
                
                }
                else if(helpInput == '3'){
						return true;
                }
	}
	else if(input.compare("3") == 0){
		//Expressions and answers will be stored on a global backup string vector
		//Also have global vector for answers but in floating point form
		//Set global previous expression "ans" to n's answer. most recent is "1" then "2" 
	}
	else if(input.compare("4") == 0){
		cout << "Thank you for using this piece of software." << endl;
		return false;
	}
	if(input.compare("back") == 0 || input.compare("Back") == 0){
		this->printMenu();
		return true;
	}
	if(input.compare("quit") == 0 || input.compare("Quit") == 0){
		cout << "Thank you for using this piece of software." << endl;
		return false;
	}
	return true;
}
