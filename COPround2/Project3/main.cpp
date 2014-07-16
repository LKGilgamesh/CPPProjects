#include "Proj3.h"
#include <iostream>
#include "tinyxml2.h"
#include <vector>
using namespace tinyxml2;
XMLDocument recipeBook;
std::vector <XMLDocument> Menu;
void insertRecipes(XMLDocument doc){
	if (doc.FirstChildElement("recipe"))
		recipeBook.InsertEndChild(doc.FirstChildElement("recipe"));
	while (!doc.LastChild()){
		if (doc.NextSiblingElement("recipe")){
			recipeBook.InsertEndChild(doc.FirstChildElement("recipe"));
		}
	}
}
int main(){
	XMLDocument newXML;
	int somestuff;
	newXML.LoadFile("example.xml");
	insertRecipes(newXML);
	std::cin >> somestuff;
	return 0;
}