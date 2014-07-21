#ifndef PROJ3_H
#define PROJ3_H

#include <fstream>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;
class Cooking{
private:
	XMLDocument *recipeBook;
	XMLDocument *inventorylist;
	XMLNode* compareNodes(XMLNode *node, XMLNode *current);
	std::vector <XMLNode*> menu;
	void addToEquipmentList(XMLNode *node);
	XMLNode* findEquipment(std::string equipment, XMLNode *node);
	XMLNode* findItem(std::string ingredient, XMLNode *node);
	XMLNode *findRecipe(XMLNode *node, std::string RecipeName);
	XMLDocument *nodeIngredientShoppingList();
	XMLDocument *nodeEquipmentShoppingList();
	void CopySubtree(XMLDocument *doc, XMLNode *copyfrom, XMLNode* copytoo, bool firstlayer);
	void adjustInventoryValues(XMLNode *node, bool enter);
	void adjustIngredientValues(XMLNode *node);
	void printIngredientsFromMenu(XMLNode *recipe);
	void findAllEquipment(XMLNode* node,XMLNode *equipmentlist,XMLDocument *doc);
	void fileOpenError();
public:
	Cooking();
	void insertRecipes(XMLNode *node);
	void printRecipe(XMLNode *node);
	void insertInventoryItem(XMLNode *node);
	void subtractInventoryItem(XMLNode *node);
	void addRecipeToMenu(std::string RecipeName);
	void removeRecipeFromMenu(std::string RecipeName);
	void increaseIngredient(std::string ingredient, float quantity, std::string unit);
	void decreaseIngredient(std::string ingredient, float quantity, std::string unit);
	void insertEquipment(std::string equipment);
	void deleteEquipment(std::string equipment);
	void resetMenu();
	void outputMenu(std::string FileName);
	void printCurrentMenu();
	void printEquipment(XMLNode *node);
	void printRecipe(std::string RecipeName);
	void printIngredientInventory(XMLNode *node, bool enter);
	void printIngredientShoppingList();
	void outputIngredientShoppingList(std::string FileName);
	void printEquipmentInventory();
	void printEquipmentList();
	void printEquipmentShoppingList();
	void outputEquipmentShoppingList(std::string FileName);
	void printIngredientList(XMLNode * node,bool enter);
};
class Handle{
private:
	std::vector <std::string> Menu;
	void OpenFile(std::string FileName);
	Cooking cooking;
public:
	Handle();
	std::ifstream input;
	std::ofstream output;	
	void inputRecipeFile(std::string FileName);
	void inputInventoryFile(std::string FileName);
	void subtractInventoryFile(std::string Filename);
	void addRecipe(std::string RecipeName);
	void removeRecipe(std::string RecipeName);
	void resetMenu();
	void outputMenu(std::string FileName);
	void printCurrentMenu();
	void printRecipe(std::string RecipeName);
	void increaseIngredientItem(std::string item);
	void reduceIngredientItem(std::string item); 
	void insertEquipmentItem(std::string item);
	void deleteEquipmentItem(std::string item);
	void printIngredientInventory();
	void printEquipmentInventory();
	void printIngredientList();
	void printIngredientShoppingList();
	void outputIngredientShoppingList(std::string FileName);
	void printEquipmentList();
	void printEquipmentShoppingList();
	void outputEquipmentShoppingList(std::string FileName);
	void help();

};

#endif //Proj3