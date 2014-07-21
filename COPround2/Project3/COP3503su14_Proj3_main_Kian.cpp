#include "Proj3.h"
#include <iostream>
#include <string>
#include <sstream>


int main(int argc, char *argv[]){
	Handle handle;
	bool VERBOSE = false;
	bool SILENT = false;
	std::string line = "";
	for (int i = 0; i < argc; i++){
		line += argv[i];
		line += " ";
	}
	if (argc != 0){
		std::istringstream ss(line);
		line = "";
		while (!ss.eof()){
			
			ss >> line;
			if (line == "-s"){
				SILENT = true;
			}
			else if (line == "-v"){
				VERBOSE = true;
			}
			else if (line == "-r"){
				line = "";
				ss >> line;
				handle.inputRecipeFile(line);
				line = "";
			}
			else if (line == "-i"){
				line = "";
				ss >> line;
				handle.inputInventoryFile(line);
				line = "";
			}
		}
	}
	
	int selection = 100;
	while (selection != 0){
		if (VERBOSE){
			std::cout
				<< "0 - exit; 1 - input recipe file <filename>; 2 - input inventory file <filename>\n"
				<< "3 - subtract inventory file <filename> 4 - add <recipe name> 5 - remove\n"
				<< "<recipe name> 6 - reset current menu 7 - output menu <filename> 8 - print\n"
				<< "current menu 9 - print <recipe name> 10 - increase <ingredient inventory item>\n"
				<< "11 - reduce <ingredient inventory item> 12 - insert <equipment inventory item>\n"
				<< "13 - delete <equipment inventory item> 14 - print ingredient inventory 15 - \n"
				<< "print equipment inventory 16 - print ingredients list 17 - print ingredient\n"
				<< "shopping list 18 - output ingredient shopping list <file> 19 - print equipment\n"
				<< "list 20 - print equipment shopping list 21 - output equipment shopping list\n"
				<< "<file> 22 - help" << std::endl;
		}

		if (!SILENT)
			std::cout << "> ";

		std::cin >> selection;
		if (std::cin.fail()){
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "invalid command" << std::endl;
			handle.help();
		}
		if (selection < 0 || selection > 22){
			std::cerr << "invalid command" << std::endl;
			handle.help();
		}
		if (selection == 0){} //closes the program
		if (selection == 1){ //input the recipe file to the cookbook
			std::string FileName;
			std::cin >> FileName;
			handle.inputRecipeFile(FileName);
		}
		if (selection == 2){ //input an inventory item to the inventory
			std::string FileName;
			std::cin >> FileName;
			handle.inputInventoryFile(FileName);

		}
		if (selection == 3){
			std::string FileName;
			std::cin >> FileName;
			handle.subtractInventoryFile(FileName);
		}
		if (selection == 4){
			std::string RecipeName;
			std::getline(std::cin, RecipeName);
			if (RecipeName[0] == ' ')
				RecipeName.erase(RecipeName.begin());
			handle.addRecipe(RecipeName);

		}
		if (selection == 5){
			std::string RecipeName;
			std::getline(std::cin, RecipeName);
			if (RecipeName[0] == ' ')
				RecipeName.erase(RecipeName.begin());
			handle.removeRecipe(RecipeName);
		}
		if (selection == 6){
			handle.resetMenu();
		}
		if (selection == 7){
			std::string FileName;
			std::getline(std::cin, FileName);
			if (FileName[0] == ' ')
				FileName.erase(FileName.begin());
			handle.outputMenu(FileName);
		}
		if (selection == 8){
			handle.printCurrentMenu();
		}
		if (selection == 9){
			std::string FileName;
			std::getline(std::cin, FileName);
			if (FileName[0] == ' ')
				FileName.erase(FileName.begin());
			handle.printRecipe(FileName);
		}
		if (selection == 10){
			std::string item;
			std::getline(std::cin, item);
			if (item[0] == ' ')
				item.erase(item.begin());
			handle.increaseIngredientItem(item);
		}
		if (selection == 11){
			std::string item;
			std::getline(std::cin, item);
			if (item[0] == ' ')
				item.erase(item.begin());
			handle.reduceIngredientItem(item);
		}
		if (selection == 12){
			std::string item;
			std::getline(std::cin, item);
			if (item[0] == ' ')
				item.erase(item.begin());
			handle.insertEquipmentItem(item);
		}
		if (selection == 13){
			std::string item;
			std::getline(std::cin, item);
			if (item[0] == ' ')
				item.erase(item.begin());
			handle.deleteEquipmentItem(item);
		}
		if (selection == 14){
			handle.printIngredientInventory();
		}
		if (selection == 15){
			handle.printEquipmentInventory();
		}
		if (selection == 16){
			handle.printIngredientList();
		}
		if (selection == 17){
			handle.printIngredientShoppingList();
		}
		if (selection == 18){
			std::string FileName;
			std::getline(std::cin, FileName);
			if (FileName[0] == ' ')
				FileName.erase(FileName.begin());
			handle.outputIngredientShoppingList(FileName);
		}
		if (selection == 19){
			handle.printEquipmentList();
		}
		if (selection == 20){
			handle.printEquipmentShoppingList();
		}
		if (selection == 21){
			std::string FileName;
			std::cin >> FileName;
			handle.outputEquipmentShoppingList(FileName);
		}
		if (selection == 22){
			handle.help();
		}
	}
	return 0;
}