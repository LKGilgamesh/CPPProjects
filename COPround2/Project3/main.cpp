#include "Proj3.h"
#include <iostream>
#include "tinyxml2.h"
#include <vector>
using namespace tinyxml2;
XMLDocument recipeBook;
void insertRecipes(XMLNode *node){
	std::string NodeName = node->ToElement()->Name();
	if (NodeName == "recipe"){
		recipeBook.InsertEndChild(node);
	}
	if (node->NextSibling())
		insertRecipes(node->NextSibling());
}
int main(){
	XMLDocument newXML;
	int somestuff;
	newXML.LoadFile("example.xml");
	XMLNode *rootNode = newXML.FirstChild();
	std::cout << rootNode->ToElement()->Name();
	insertRecipes(rootNode);
	std::cin >> somestuff;
	return 0;
}