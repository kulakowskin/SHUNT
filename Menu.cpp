#include <iostream>
#include <exception>
#include "Menu.h"
using namespace std;


bool Menu::printMenu(){
	cout << "\n\t1.) Compute new expression" << endl;
	cout << "\t2.) Help and usability information" << endl;
	cout << "\t3.) Review previous expression and answers" << endl;
	cout << "\t4.) Quit" << "\n" << endl;
	bool choice = this->readChoice();	
	return choice == true ? true : false;
}
void Menu::printMenu_basic(){
	cout << "\n\t\t\t\tGroup 14 - 1\n- Jayson Salkey\n- Xiaoxi Zheng\n- Cam Cooper\n- Kyle Goins\n- Nicole Kulakowski\n- Jessan Cherian.\n\n\n";
	cout << "Fractional/Decimal? [Y/n] ";
	cin >> this->frac_float;
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
		this->enterExpression(this->frac_float);
	}
	else if(input.compare("2") == 0){
		helpMenu:
                //enter program dialog mode that details how to specify math operations
                cout<<"Welcome to the help menu!\n"<<endl;
                cout<<"\t1.)Display general input syntax expectations and usability information"<<endl;
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
                	cout<<"Reminder: !!PLEASE INCLUDE SPACES FOR EVERY INTENDED OPERATIONS!! "<<endl;
                	cout<<"Reminder: The results from each operation is SAVED,users are allowed to use the 'ans' keyword "<<endl;
                	cout<<"\t Example: ans + 25"<<endl;
                	cout<<"===============================================================================================" <<endl;
                	cout<<"INPUT EXPECTATIONS: "<<endl;
                        cout<<"1.)Power: "<<endl;
                        cout<<"\t x to the power of y == x^y"<<endl;
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
                        cout<<" ans * 5/3 "<<endl;
                
                }
                else if(helpInput == '3'){
						return true;
                }
	}
	else if(input.compare("3") == 0){
		int a;
		cout << "\tEnter the number of the previous\n\texpression/answer you would like to receive. " << endl;
		cin >> a;
		cout << "\n" << this->getPrevExp(a)<< "\n" << endl;  
	}
	else if(input.compare("4") == 0){
		cout << "Thank you for using this piece of software." << endl;
		this->writeFile();
		return false;
	}
	if(input.compare("back") == 0 || input.compare("Back") == 0){
		this->printMenu();
		return true;
	}
	if(input.compare("quit") == 0 || input.compare("Quit") == 0){
		cout << "Thank you for using this piece of software." << endl;
		cout << "All your results are saved in a .txt file!" << endl;
		this->writeFile();
		return false;
	}
	return true;
}
