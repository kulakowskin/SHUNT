#include "Menu.h"
#include <iostream>
using namespace std;
int main(){
	Menu* menu = new Menu();
	menu->printMenu_basic();
	while(true){		
		if(menu->printMenu() == false){
			return 0;
		}	
	}
	return 0;
}

