#include <iostream>
#include <unistd.h>
#include "stages.hpp"

using namespace std;

int main(){
	if(getuid() == 0){
		//Info
		cout << "Welcome to \033[32mpacofstrap\033[0m \033[31mbeta!\033[0m Which stage are you on?" << endl;
		cout << "1: Before installation, 2: In archiso." << endl;
		
		//varibles
		int stage;

		//get user input
		cin >> stage;

		switch(stage){
			case 1:{ //control
				firststage();
				return 0;
			}
			case 2:{ //control
				secondstage();
				return 0;
			}
			default:{ //ERROR CHECK
				cout << "\033[31mThis option doesn't exist!\033[0m" << endl; //ERROR CHECK
			}
		}
	}else{
	cout << "You have to be \033[31mroot.\033[0m" << endl; //ERROR CHECK
}
}
