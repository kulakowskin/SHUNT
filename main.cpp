#include "Menu.h"
#include <iostream>
using namespace std;
int main(){
	while(true){
		Menu* menu = new Menu();
		menu->printMenu_basic();
		if(menu->printMenu() == false){
			return 0;
		}	
	}
	return 0;
}

