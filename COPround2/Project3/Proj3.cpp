#include "tinyxml2.h"
#include <string>
#include "Proj3.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <sstream>
using namespace tinyxml2;
Cooking::Cooking(){
	recipeBook = new XMLDocument();
	inventorylist = new XMLDocument();

	recipeBook->InsertEndChild(recipeBook->NewElement("cookbook"));
	inventorylist->InsertEndChild(inventorylist->NewElement("inventory"));
	
	XMLElement * IL = inventorylist->NewElement("ingredientlist");
	inventorylist->FirstChildElement()->InsertEndChild(IL);
	XMLElement * EL = inventorylist->NewElement("equipmentlist");
	inventorylist->FirstChild()->InsertEndChild(EL);
}
void Cooking::insertRecipes(XMLNode *node){
	std::string NodeName = node->ToElement()->Name();
	if (NodeName == "cookbook"){
		insertRecipes(node->FirstChild());
	}
	if (NodeName == "recipe"){
		CopySubtree(recipeBook, node, recipeBook->FirstChild(), false);
	}
	if (node->NextSibling())
		insertRecipes(node->NextSibling());
}
void Cooking::printRecipe(XMLNode *node){
	std::string nodeValue = node->Value();
	if (node->ToElement()){
		if (nodeValue == "ingredientlist"){
			std::cout << "  Ingredients" << std::endl;
		}
		else if (nodeValue == "preparation"){
			std::cout << "  Preparation" << std::endl;
		}
		else if (nodeValue == "ingredient"){
			std::string str = "	";
			if (node->FirstChildElement("quantity")){
				str += node->FirstChildElement("quantity")->GetText();
				str += " ";
			}
			if (node->FirstChildElement("unit")){			
				str += node->FirstChildElement("unit")->GetText();
				str += " ";
			}
			str += node->FirstChildElement("fooditem")->GetText();
			
			std::cout << str << std::endl;

		}
		else if (nodeValue == "step"){
			std::string str = "	";
			str += node->FirstChild()->Value();
			std::cout << str << std::endl;

		}
		else if (nodeValue == "title"){
			if (node->FirstChild()->ToText()){
				std::string str = node->FirstChild()->ToText()->Value();
				std::cout << str << std::endl;
			}
		}


	}

	if (node->FirstChild())
		printRecipe(node->FirstChild());
	if (node->NextSibling())
		printRecipe(node->NextSibling());



}
void Cooking::printEquipment(XMLNode *node){
	std::string nodeValue = node->Value();
	if (nodeValue == "equipmentlist"){
		std::cout << "  equipment list" << std::endl;
	}
	else if (nodeValue == "equipment"){
		std::string str = node->FirstChild()->Value();
		std::cout << "	" << str << std::endl;

	}
	if (node->FirstChild())
		printEquipment(node->FirstChild());
	if (node->NextSibling())
		printEquipment(node->NextSibling());
}
XMLNode * Cooking::compareNodes(XMLNode *node,XMLNode *current){
	XMLNode * found = NULL;
	if (current->ShallowEqual(node)){
		found = current;

	}
	if (current->FirstChild() && found == NULL){
		found = compareNodes(node, current->FirstChild());
	}
	if (current->NextSibling() && found == NULL)
		found = compareNodes(node, current->NextSibling());
	return found;
}

void Cooking::addToEquipmentList(XMLNode *node){
	std::string nodeValue = node->Value();
	if (nodeValue == "equipmentlist"){
		addToEquipmentList(node->FirstChild());
	}
	if (nodeValue == "equipment"){
		if (node->FirstChild()){
			XMLNode *found = compareNodes(node, inventorylist->FirstChild());
			if (found == NULL)
				inventorylist->FirstChildElement("inventory")->FirstChildElement("equipmentlist")->InsertEndChild(node);
		}

	}
	if (nodeValue == "ingedient"){
		if (node->FirstChild()){
			XMLNode *found = compareNodes(node, inventorylist->FirstChild());
			if (found == NULL)
				inventorylist->FirstChildElement("inventory")->FirstChildElement("ingredientlist")->InsertEndChild(node);
		}

	}
	if (node->NextSibling()){
		addToEquipmentList(node->NextSibling());
	}
}
XMLNode *Cooking::findItem(std::string ingredient, XMLNode *node){
	XMLNode * found = NULL;
	std::string str;
	if (node->Value())
		str = node->Value();
	if (ingredient == str){
		found = node->Parent();
	}
	if (node->FirstChild() && found == NULL)
		found = findItem(ingredient, node->FirstChild());
	if (node->NextSibling() && found == NULL)
		found = findItem(ingredient, node->NextSibling());
	return found;
}
void Cooking::adjustInventoryValues(XMLNode *node, bool enter){
	if (inventorylist->FirstChild()->FirstChildElement("ingredientlist")->FirstChild() && enter == false){
		
		std::string nodeValue;
		if (node != NULL)
			nodeValue = node->Value();
		
		if (nodeValue == "ingredient"){
			if (node->FirstChild()){
				std::string nodeValue2 = node->FirstChildElement("fooditem")->GetText();
				XMLNode *found = findItem(nodeValue2, inventorylist->FirstChild());
				found = found->Parent();
				if (found != NULL){
					if (found->FirstChild()->NextSibling()){
						float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
						sum += atof(node->FirstChildElement("quantity")->FirstChild()->Value());
						std::ostringstream ss;
						ss << sum;
						std::string sumstring(ss.str());

						node->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
		
						XMLNode *parent = found->Parent();
						parent->DeleteChild(found);
					}
					
						
					

				}

			}
		}
		if (node->NextSibling())
			adjustInventoryValues(node->NextSibling(), false);

	}
	else if (inventorylist->FirstChild()->FirstChildElement("equipmentlist")->FirstChild() && enter == true){
		std::string nodeValue;
		if (node != NULL)
			nodeValue = node->Value();

		if (nodeValue == "equipment"){
			if (node->FirstChild()){
				std::string nodeValue2 = node->FirstChild()->Value();
				XMLNode * found = findItem(nodeValue2, inventorylist->FirstChild());
				
				if (found != NULL){
					found = found->Parent();
					XMLNode *parent = node->Parent();
					XMLNode *prev = node;
					
					if (node->NextSibling()){
						node = node->NextSibling();
						adjustInventoryValues(node, true);
					}
					else
						node = NULL;
					parent->DeleteChild(prev);
				}
				else{
					if (node->NextSibling())
						adjustInventoryValues(node->NextSibling(), true);
				}
			}
		}
		
	}
}


void Cooking::insertInventoryItem(XMLNode *node){
	std::string nodeValue = node->ToElement()->Name();
	if (nodeValue == "inventory"){
		insertInventoryItem(node->FirstChild());
	}
	if (nodeValue == "equipmentlist"){
		if (node->FirstChild()){
			adjustInventoryValues(node->FirstChild(), true);
			CopySubtree(inventorylist, node->FirstChild(), inventorylist->FirstChild()->FirstChildElement("equipmentlist"), true);
		}

	}
	if (nodeValue == "ingredientlist"){
		if (node->FirstChild()){
			adjustInventoryValues(node->FirstChild(),false);
			CopySubtree(inventorylist, node->FirstChild(), inventorylist->FirstChild()->FirstChildElement("ingredientlist"), true);
		}
	}
	if (node->NextSibling()){
		insertInventoryItem(node->NextSibling());
	}

}
void Cooking::subtractInventoryItem(XMLNode *node){
	std::string nodeValue = node->ToElement()->Name();
	if (nodeValue == "inventory" || nodeValue == "equipmentlist" || nodeValue == "ingredientlist"){
		subtractInventoryItem(node->FirstChild());
	}
	if (nodeValue == "equipment"){
		if (node->FirstChild()){
			std::string nodeValue2 = node->FirstChild()->Value();
			XMLNode *found = findItem(nodeValue2, inventorylist->FirstChild());
			if (found == NULL){}
			else{
				XMLNode *parent = found->Parent();
				parent->DeleteChild(found);

			}
		}

	}
	if (nodeValue == "ingredient"){
		if (node->FirstChild()){
			std::string nodeValue2 = node->FirstChildElement("fooditem")->GetText();
			XMLNode *found = findItem(nodeValue2, inventorylist->FirstChild());
			
			if (found == NULL){}
				
			else{
				found = found->Parent();
				if (found->FirstChild()->NextSibling()){
					float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
					sum -= atof(node->FirstChildElement("quantity")->FirstChild()->Value());
					if (sum >  0){
						std::ostringstream ss;
						ss << sum;
						std::string sumstring(ss.str());

						found->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
					}
					else{
						XMLNode *parent = found->Parent();
						parent->DeleteChild(found);
					}
					
				}
			}
		}

	}
	if (node->NextSibling()){
		subtractInventoryItem(node->NextSibling());
	}

}
void Cooking::addRecipeToMenu(std::string RecipeName){
	XMLNode * found = findItem(RecipeName, recipeBook->FirstChild());
	bool inMenu = false;
	for (int i = 0; i < menu.size(); i++){
		if (found->Parent() == menu[i])
			inMenu = true;
	}
	if (found != NULL && inMenu == false){
		menu.push_back(found->Parent());
	}
	
}
void Cooking::removeRecipeFromMenu(std::string RecipeName){
	if (menu.size() >= 1){
		int menusize = menu.size();
		for (int i = menusize- 1; i >= 0; i--){
			std::string str = menu[i]->FirstChildElement("title")->GetText();
			if (str == RecipeName)
				menu.erase(menu.begin() + i);
		}
	}
}
void Cooking::resetMenu(){
	menu.clear();
}
void Cooking::outputMenu(std::string FileName){
	std::string tempName = "./" + FileName + ".xml";
	XMLDocument *menuToXML = new XMLDocument;
	menuToXML->InsertEndChild(menuToXML->NewElement("Menu"));
	int menusize = menu.size();
	for (int i = 0; i < menusize; i++){
		CopySubtree(menuToXML, menu[i], menuToXML->FirstChild(), true);
	}
	bool saveokay = menuToXML->SaveFile(tempName.c_str());
	if (saveokay)
		std::cerr << "file did not save correctly" << std::endl;
}
void Cooking::printCurrentMenu(){
	if (menu.size() >= 1){
		int menusize = menu.size();
		for (int i = 0; i < menusize; i++){
			std::string str = menu[i]->FirstChildElement("title")->GetText();
			std::cout << str << std::endl;
		}
	}

}
void Cooking::increaseIngredient(std::string ingredient, float quantity, std::string unit){
	XMLNode *found = findItem(ingredient, inventorylist->FirstChild());
	if (found != NULL){
		found = found->Parent();
		if (quantity != 0){
			float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
			sum += quantity;
			std::ostringstream ss;
			ss << sum;
			std::string sumstring(ss.str());

			found->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
		}
		else{
			float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
			sum += 1;
			std::ostringstream ss;
			ss << sum;
			std::string sumstring(ss.str());

			found->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
		}
		if (unit != ""){
			
			XMLNode *found2 = findItem(unit, found);
			if (found2 != NULL){}
			else{
				found->FirstChildElement("unit")->FirstChild()->SetValue(unit.c_str());
			}
		}
	}
	else{
		XMLNode * node = inventorylist->FirstChild()->FirstChildElement("ingredientlist")->InsertEndChild(inventorylist->NewElement("ingredient"));
		XMLNode * fooditem = node->InsertEndChild(inventorylist->NewElement("fooditem"));
		fooditem->InsertEndChild(inventorylist->NewText(ingredient.c_str()));
		if (quantity != 0){
			XMLNode * quant = node->InsertEndChild(inventorylist->NewElement("quantity"));
			std::ostringstream ss;
			
			ss << quantity;
			std::string quants(ss.str());
			quant->InsertEndChild(inventorylist->NewText(quants.c_str()));
		}
		if (unit != ""){
			XMLNode * units= node->InsertEndChild(inventorylist->NewElement("unit"));
			units->InsertEndChild(inventorylist->NewText(unit.c_str()));
		}

	}

	
	
}
void Cooking::decreaseIngredient(std::string ingredient, float quantity, std::string unit){
	XMLNode *found = findItem(ingredient, inventorylist->FirstChild());
	if (found != NULL){
		found = found->Parent();
		if (quantity != 0){
			float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
			sum -= quantity;
			if (sum > 0){
				std::ostringstream ss;
				ss << sum;
				std::string sumstring(ss.str());

				found->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
			}
			else{
				if (sum < 0)
					std::cerr << "quantity removed was more than was was available!" << std::endl;
				XMLNode *parent = found->Parent();
				parent->DeleteChild(found);
			}
		}
		else{
			float sum = atof(found->FirstChildElement("quantity")->FirstChild()->Value());
			sum -= 1;
			if (sum > 0){
				std::ostringstream ss;
				ss << sum;
				std::string sumstring(ss.str());
				found->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
			}
			else{
				XMLNode *parent = found->Parent();
				parent->DeleteChild(found);
			}
		}
	}
	else{
		//some form of error statement here
	}
}
XMLNode *Cooking::findEquipment(std::string equipment, XMLNode *node){
	XMLNode *found = NULL;
	if (node == NULL){
		return findEquipment(equipment, inventorylist->FirstChild());
	}
	std::string nodeValue = node->Value();
	if (nodeValue == "equipmentlist" || nodeValue == "inventorylist")
		return findEquipment(equipment, node->FirstChild());
	if (nodeValue == "equipment"){
		if (node->ToText()){
			nodeValue = node->ToText()->Value();
			if (nodeValue == equipment){
				found = node;

			}
		}
		if (node->NextSibling() && found == false)
			findEquipment(equipment, node->NextSibling());
	}
	return found;
}
void Cooking::insertEquipment(std::string equipment){
	if (findItem(equipment, inventorylist->FirstChild()) == NULL){
		XMLNode * node = inventorylist->FirstChild()->FirstChildElement("equipmentlist")->InsertEndChild(inventorylist->NewElement("equipment"));
		node->InsertEndChild(inventorylist->NewText(equipment.c_str()));
	}
	else
		std::cerr << equipment << "is already in the inventory!" << std::endl;
}
void Cooking::deleteEquipment(std::string equipment){
	XMLNode *childToDelete = findItem(equipment, inventorylist->FirstChild());
	if (childToDelete != NULL){
		XMLNode *parent = childToDelete->Parent();
		parent->DeleteChild(childToDelete);
	}
	else{
		std::cerr << equipment << "was not in the inventory!" << std::endl;
	}
}
XMLNode *Cooking::findRecipe(XMLNode *node,std::string RecipeName){
	XMLNode * found = NULL;
	if (recipeBook->RootElement())
		std::string str= recipeBook->FirstChild()->ToElement()->Name();
	if (node == NULL){
		return findRecipe(recipeBook->FirstChild(),RecipeName);
	}
	std::string menuAddition = node->Value();
	if (menuAddition == "cookbook" || menuAddition == "recipe" || menuAddition == "title"){
		if (node->FirstChild())
			return findRecipe(node->FirstChild(), RecipeName);
	}
	if (menuAddition == RecipeName){
		found = node->Parent()->Parent();
		return found;
	}
	if (node->NextSibling() && found == NULL)
		return findRecipe(node->NextSibling(), RecipeName);
	return found;
}
void Cooking::printRecipe(std::string RecipeName){
	XMLNode * foundRecipe = findRecipe(NULL, RecipeName);
	if (foundRecipe != NULL){
		printRecipe(foundRecipe);
		std::cout << "  equipment" << std::endl;
		printEquipment(foundRecipe);
	}
}
void Cooking::printIngredientInventory(XMLNode *node, bool enter){
	if (node == NULL && enter == false){
		std::cout << "  ingredient list" << std::endl;
		printIngredientInventory(inventorylist->FirstChild(), true);
	}
	else{
		XMLNode * in = inventorylist->FirstChild()->FirstChildElement("ingredientlist")->FirstChild();
		if (in != NULL){
			std::string nodeValue = node->Value();
			if (nodeValue == "inventory" || nodeValue == "ingredientlist"){

				printIngredientInventory(node->FirstChild(), true);
			}
			if (nodeValue == "ingredient"){
				std::cout << "	";
				std::string str;
				if (node->FirstChildElement("quantity")){
					str += node->FirstChildElement("quantity")->GetText();
					str += " ";
				}
				if (node->FirstChildElement("unit")){
					str += node->FirstChildElement("unit")->GetText();
					str += " ";
				}
				str += node->FirstChildElement("fooditem")->GetText();
				std::cout << str << std::endl;
			}
			if (node->NextSibling())
				printIngredientInventory(node->NextSibling(), true);
		}
	}
}
void Cooking::printIngredientsFromMenu(XMLNode *recipe){
	std::string nodeValue = recipe->Value();
	if (nodeValue == "ingredient"){
		std::cout << "	";
		std::string str;
		if (recipe->FirstChildElement("quantity")){
			str += recipe->FirstChildElement("quantity")->GetText();
			str += " ";
		}
		if (recipe->FirstChildElement("unit")){
			str += recipe->FirstChildElement("unit")->GetText();
			str += " ";
		}
		str += recipe->FirstChildElement("fooditem")->GetText();
		std::cout << str << std::endl;
	}
	if (recipe->NextSibling())
		printIngredientsFromMenu(recipe->NextSibling());
}
void Cooking::printIngredientList(XMLNode *node,bool enter){
	if (menu.size() >= 1){
		int menusize = menu.size();
		for (int i = 0; i < menusize; i++){
			printIngredientsFromMenu(menu[i]->FirstChildElement("ingredientlist")->FirstChild());
		}
	}
}
void Cooking::adjustIngredientValues(XMLNode *node){
	std::string nodeValue = node->Value();
	if (nodeValue == "ingredient"){
		if (node->FirstChild()){
			std::string nodeValue2 = node->FirstChildElement("fooditem")->GetText();
			XMLNode *found = findItem(nodeValue2, inventorylist->FirstChild());
			
			if (found != NULL){
				found = found->Parent();
				if (found->FirstChild()->NextSibling()){
					float sum = atof(node->FirstChildElement("quantity")->FirstChild()->Value()); 
					sum -= atof(found->FirstChildElement("quantity")->FirstChild()->Value());
					if (sum >  0){
						std::ostringstream ss;
						ss << sum;
						std::string sumstring(ss.str());

						node->FirstChildElement("quantity")->FirstChild()->SetValue(sumstring.c_str());
						if (node->NextSibling())
							adjustIngredientValues(node->NextSibling());
					}
					else{
						XMLNode *prev = node;
						XMLNode *parent = prev->Parent();
						if (node->NextSibling()){
							node = node->NextSibling();
							adjustIngredientValues(node);
						}
						parent->DeleteChild(prev);
					}
				}
				else{
					if (node->NextSibling())
						adjustIngredientValues(node->NextSibling());
				}



			}
			else{
				if (node->NextSibling())
					adjustIngredientValues(node->NextSibling());
			}

		}
	}
	
}
XMLDocument *Cooking::nodeIngredientShoppingList(){
	XMLDocument *shoppinglist = new XMLDocument;
	XMLNode * ingredientlist = shoppinglist->InsertEndChild(shoppinglist->NewElement("ingredientlist"));
	if (menu.size() > 0){
		for (int i = 0; i < menu.size(); i++){
			CopySubtree(shoppinglist, menu[i]->FirstChildElement("ingredientlist")->FirstChild(), ingredientlist, true);
		}
	
	}
	if (!shoppinglist->FirstChild()->NoChildren()){
		adjustIngredientValues(ingredientlist->FirstChild());
		
	}
	return shoppinglist;
}
void Cooking::printIngredientShoppingList(){
	XMLNode *ingredientsneeded = nodeIngredientShoppingList()->FirstChild()->FirstChildElement("ingredient");
	std::cout << "Ingredients" << std::endl;
	for (XMLNode *e = ingredientsneeded; e != NULL; e = e->NextSibling()){
		std::cout << "	";
		std::string str;
		if (e->FirstChildElement("quantity")){
			str += e->FirstChildElement("quantity")->GetText();
			str += " ";
		}
		if (e->FirstChildElement("unit")){
			str += e->FirstChildElement("unit")->GetText();
			str += " ";
		}
		str += e->FirstChildElement("fooditem")->GetText();
		std::cout << str << std::endl;
	}
	
}
void Cooking::outputIngredientShoppingList(std::string FileName){
	XMLDocument *shoppinglist = nodeIngredientShoppingList();
	if (shoppinglist->FirstChild()->FirstChild()){

		bool saveokay = shoppinglist->SaveFile(FileName.c_str());
		if (saveokay)
			std::cerr << "save file failed" << std::endl;
	}
	
}
void Cooking::printEquipmentInventory(){
	printEquipment(inventorylist->FirstChild());
}
void Cooking::printEquipmentList(){
	std::cout << "  equipment list" << std::endl;
	for (int i = 0; i < menu.size(); i++){
		printEquipment(menu[i]);
	}
}
void Cooking::printEquipmentShoppingList(){
	XMLNode *equipmentneeded = nodeEquipmentShoppingList()->FirstChild()->FirstChildElement("equipment");
	std::cout << "  Equipmentlist" << std::endl;
	for (XMLNode *e = equipmentneeded; e != NULL; e = e->NextSibling()){
		std::cout << "	";
		std::string str = e->FirstChild()->Value();
		
		std::cout << str << std::endl;
	}
}
void Cooking::outputEquipmentShoppingList(std::string FileName){
	XMLDocument *shoppinglist = nodeEquipmentShoppingList();
	if (shoppinglist->FirstChild()->FirstChild()){
		bool saveokay = shoppinglist->SaveFile(FileName.c_str());
		if (saveokay)
			std::cerr << "save to file failed" << std::endl;
	}
}
void Cooking::findAllEquipment(XMLNode *node,XMLNode *equipmentlist,XMLDocument *doc){
	std::string nodeValue = node->Value();
	if (nodeValue == "equipment"){
		XMLNode * found = equipmentlist->InsertEndChild(node->ShallowClone(doc));
		found->InsertEndChild(node->FirstChild()->ShallowClone(doc));
	}
	if (node->FirstChild())
		findAllEquipment(node->FirstChild(),equipmentlist,doc);
	if (node->NextSibling())
		findAllEquipment(node->NextSibling(),equipmentlist,doc);
}
XMLDocument *Cooking::nodeEquipmentShoppingList(){
	XMLDocument *shoppinglist = new XMLDocument;
	XMLNode * equiplist = shoppinglist->InsertEndChild(shoppinglist->NewElement("equipmentlist"));
	for (int i = 0; i < menu.size(); i++){
		findAllEquipment(menu[i], equiplist,shoppinglist);
	}
	adjustInventoryValues(equiplist->FirstChild(), true);

	return shoppinglist;
}
void Cooking::CopySubtree(XMLDocument *doc, XMLNode *copyfrom, XMLNode *copytoo, bool firstlayer){
	if (copyfrom != NULL){
		XMLNode* copy = copyfrom->ShallowClone(doc);
		copytoo->InsertEndChild(copy);
		XMLNode * tosee = copytoo->Parent();
		if (copyfrom->FirstChild())
			CopySubtree(doc, copyfrom->FirstChild(), copy, true);
		if (copyfrom->NextSibling() && firstlayer == true)
			CopySubtree(doc, copyfrom->NextSibling(), copytoo, true);
	}
}




Handle::Handle(){}

void Handle::inputRecipeFile(std::string FileName){
	std::string tempName = "./" + FileName + ".xml";
	XMLDocument recipe;
	bool loadokay = recipe.LoadFile(tempName.c_str());
	if (!loadokay){
		XMLNode *rootNode = recipe.FirstChild();
		cooking.insertRecipes(rootNode);
	}
	else
		std::cerr << "load file failed" << std::endl;

}
void Handle::inputInventoryFile(std::string FileName){
	std::string tempName = "./" + FileName + ".xml";
	XMLDocument inventorylist;
	bool loadokay = inventorylist.LoadFile(tempName.c_str());
	if (!loadokay){
		XMLNode *rootNode = inventorylist.FirstChild();
		cooking.insertInventoryItem(rootNode);
	}
	else
		std::cerr << "load file failed" << std::endl;
}
void Handle::subtractInventoryFile(std::string FileName){
	std::string tempName = "./" + FileName + ".xml";
	XMLDocument inventorylist;
	bool loadokay = inventorylist.LoadFile(tempName.c_str());
	if (!loadokay){
		XMLNode *rootNode = inventorylist.FirstChild();
		cooking.subtractInventoryItem(rootNode);
	}
	else
		std::cerr << "load file failed" << std::endl;
}
void Handle::addRecipe(std::string RecipeName){
	cooking.addRecipeToMenu(RecipeName);
}
void Handle::removeRecipe(std::string RecipeName){
	cooking.removeRecipeFromMenu(RecipeName);
}
void Handle::resetMenu(){
	cooking.resetMenu();
}
void Handle::outputMenu(std::string FileName){
	cooking.outputMenu(FileName);
}
void Handle::printCurrentMenu(){
	cooking.printCurrentMenu();
}
void Handle::printRecipe(std::string RecipeName){
	cooking.printRecipe(RecipeName);
}
void Handle::increaseIngredientItem(std::string item){
	int stringSize = item.size();
	bool quantityFound = false;
	bool unitFound = false;
	std::string ingredient;
	std::string quantitystring;
	std::string unit;
	for (int i = 0; i < stringSize; i++){
		if (item[i] == ' ' && quantityFound == true){} //ignore this if found
		else if (item[i] == ']'){}	//ignore this if found
		else if (item[i] == '['){
			if (quantityFound == false)
				quantityFound = true;
			else
				unitFound = true;
		}
		
		else if (quantityFound == true && unitFound == true){
			unit += item[i];
		}
		else if (quantityFound == true && unitFound == false){
			quantitystring += item[i];
		}
		else
			ingredient += item[i];
	}
	float quantity = atof(quantitystring.c_str());
	cooking.increaseIngredient(ingredient,quantity,unit);
}
void Handle::reduceIngredientItem(std::string item){
	int stringSize = item.size();
	bool quantityFound = false;
	bool unitFound = false;
	std::string ingredient;
	std::string quantitystring;
	std::string unit;
	for (int i = 0; i < stringSize; i++){
		if (item[i] == ' ' && quantityFound == true){} //ignore this if found
		else if (item[i] == ']'){}	//ignore this if found
		else if (item[i] == '['){
			if (quantityFound == false)
				quantityFound = true;
			else
				unitFound = true;
		}

		else if (quantityFound == true && unitFound == true){
			unit += item[i];
		}
		else if (quantityFound == true && unitFound == false){
			quantitystring += item[i];
		}
		else
			ingredient += item[i];
	}
	float quantity = atof(quantitystring.c_str());
	cooking.decreaseIngredient(ingredient, quantity, unit);
}
void Handle::insertEquipmentItem(std::string item){
	cooking.insertEquipment(item);
}
void Handle::deleteEquipmentItem(std::string item){
	cooking.deleteEquipment(item);
}
void Handle::printIngredientInventory(){
	cooking.printIngredientInventory(NULL, false);
}
void Handle::printEquipmentInventory(){
	cooking.printEquipmentInventory();
}
void Handle::printIngredientList(){
	std::cout << "ingredientlist" << std::endl;
	cooking.printIngredientList(NULL,false);
}
void Handle::printIngredientShoppingList(){
	cooking.printIngredientShoppingList();
}
void Handle::outputIngredientShoppingList(std::string FileName){
	std::string tempName =FileName + ".xml";
	cooking.outputIngredientShoppingList(tempName);
}
void Handle::printEquipmentList(){
	cooking.printEquipmentList();
}
void Handle::printEquipmentShoppingList(){
	cooking.printEquipmentShoppingList();
}
void Handle::outputEquipmentShoppingList(std::string FileName){
	std::string tempName = FileName + ".xml";
	cooking.outputEquipmentShoppingList(tempName);
		
}
void Handle::help(){
	std::cout 
		<< "================================================================================" 
		<< "The numbered commands are as follows : \n"
		<< "0.  exit\n"
		<< "1.  input a recipe file <filename>\n"
		<< "2.  input an inventory file <filename>\n"
		<< "3.  subtract recipes that match those from input file <filename>\n"
		<< "4.  add a recipe to the menu <recipe name>\n"
		<< "5.  remove a recipe from the menu <recipe name>\n"
		<< "6.  reset current menu\n"
		<< "7.  output menu to a XML file <filename>\n"
		<< "8.  print menu to console\n"
		<< "9.  print a recipe if stored already <recipe name>\n"
		<< "10. increase inventory item <ingredient inventory item>\n"
		<< "11. reduce inventory item <ingredient inventory item>\n"
		<< "12. insert equipment item <equipment inventory item>\n"
		<< "13. delete equipment item <equipment inventory item>\n"
		<< "14. print ingredient inventory to console\n"
		<< "15. print equipment inventory to console\n"
		<< "16. print ingredients needed for all recipes\n"
		<< "17. print ingredients missing for all recipes\n"
		<< "18. output ingredients missing for all recipes to XML <filename>\n"
		<< "19. print equipment needed for all recipes\n"
		<< "20. print equipment missing for all recipes\n"
		<< "21. output equipment missing for all recipes to XML <filename>\n"
		<< "22. help\n"
		<< "================================================================================" << std::endl;
}