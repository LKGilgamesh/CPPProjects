#ifndef PROJ3_H
#define PROJ3_H

#include <fstream>
#include <vector>
class CookBook{
private:
	XMLDocument recipeBook;
public:
	CookBook();
	void insertRecipes(XMLNode *node);
	void printRecipeBook(XMLNode *node);
};
class Inventory{
public:
	Inventory();
};
class Handle{
private:
	std::vector <std::string> Menu;
	void OpenFile(std::string FileName);
	CookBook cookbook;
	Inventory inventory;
public:
	Handle();
	std::ifstream input;
	std::ofstream output;	
	void inputRecipeFile(std::string FileName);
	void inputInventoryFile(std::string FileName);
	void subtractInventoryFile(std::string Filename);
	void addRecipe(std::string RecipeName);
	void increaseInventoryItem(std::string item); //look at this later, doesnt make any sense.
	void reduceInventoryItem(std::string item); //this too.
	void insertInventoryItem(std::string item);
	void deleteInventoryItem(std::string item);
	void printIngredientInventory();
	void printEquipmentInventory();
	void printIngredientList();
	void printIngredientShoppingList();
	void outputIngredientShoppingList(std::string FileName);
	void printEquipmentList();
	void printEquipmentShoppingList();
	void outputEquipmentShoppingList();
	void help();

};

#endif //Proj3