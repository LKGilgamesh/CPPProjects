#include "tinyxml2.h"
#include <string>
#include "Proj3.h"
#include <iostream>
#include <exception>

using namespace tinyxml2;

void CookBook::insertRecipes(XMLNode *node){
	std::string NodeName = node->ToElement()->Name();
	if (NodeName == "cookbook"){
		insertRecipes(node->FirstChild());
	}
	if (NodeName == "recipe"){
		recipeBook.InsertEndChild(node);
	}
	if (node->NextSibling())
		insertRecipes(node->NextSibling());
}
void CookBook::printRecipeBook(XMLNode *node){
	if (node->Value()){
		const char * NodeName = node->Value();
		printf("%s\n", NodeName);
		//std::cout << std::endl;
	}

	if (node->FirstChild())
		printRecipeBook(node->FirstChild());
	if (node->NextSibling())
		printRecipeBook(node->NextSibling());

}
Handle::Handle(){}

void Handle::inputRecipeFile(std::string FileName){
	std::string tempName = "./" + FileName + ".xml";
	XMLDocument recipe;
	recipe.LoadFile(tempName.c_str());
	XMLNode *rootNode = recipe.FirstChild();
	cookbook.insertRecipes(rootNode);
}
