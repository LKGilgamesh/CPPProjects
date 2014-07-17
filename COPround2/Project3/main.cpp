#include "Proj3.h"
#include <iostream>
#include <string>



int main(){
	Handle handle;
	int selection = 100;
	while (selection != 0){
		std::cout << "> ";
		std::cin >> selection;

		if (selection == 0){} //closes the program
		if (selection == 1){ //input the recipe file to the cookbook
			std::string FileName;
			std::cin >> FileName;
			handle.inputRecipeFile(FileName);
		}
		if (selection == 2){

		}
		if (selection == 3){

		}
		if (selection == 4){


		}
		if (selection == 5){

		}
		if (selection == 6){

		}
		if (selection == 7){

		}
		if (selection == 8){

		}
		if (selection == 9){

		}
		if (selection == 10){

		}
		if (selection == 11){

		}
		if (selection == 12){

		}
		if (selection == 13){

		}
		if (selection == 14){

		}
		if (selection == 15){

		}
		if (selection == 16){

		}
		if (selection == 17){

		}
		if (selection == 18){

		}
		if (selection == 19){

		}
		if (selection == 20){


		}
		if (selection == 21){

		}
		if (selection == 22){

		}
	}
	return 0;
}