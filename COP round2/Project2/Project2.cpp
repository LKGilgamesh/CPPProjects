#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Project2.h"
#include <exception>


std::ifstream input;
std::ofstream output;

SetIO::SetIO(){
	counter = 0;
	for (int i = 0; i < 100; i++){
		setList[i] = "";
	}
}
void SetIO::addToSet(std::string &str, int &number){
	if (findInSet(str) == -1){
		counter++;
		setList.push_back(str);
		setCount.push_back(number);
	}
}

void SetIO::rmFromSet(int index){
	setList.erase(setList.begin() + index);
	setCount.erase(setCount.begin() + index);
	counter--;
}
int SetIO::findInSet(std::string &str){
	int pos = -1;
	for (int i = 0; i < counter; i++){
		if (setList[i] == str){
			pos = i;
		}
	}
	return pos;
}
void SetIO::clearSet(){
	setList.clear();
	setCount.clear();
}
void SetIO::printList(){
	for (int i = 0; i <= counter; i++){
			std::cout << setList[i] << std::endl;
	}
}
void SetIO::openI(std::string &name){
	name = "./" + name + ".txt";
	input.open(name.c_str());
	if (input.fail())
		std::cout << "Unable to open file: " << name << std::endl;
}

void SetIO::closeI(){
	input.close();
	input.clear();
}

void SetIO::obtainLine(std::string &item, int &count){
	std::string tempString;
	getline(std::cin, tempString);
	std::istringstream record(tempString);
	record >> item >> count;
	bool read_fail = false;
	if (read_fail = record.fail()){
		std::cout << "line failure" << std::endl;
	}
	record >> tempString;
	if (!record.eof()){
		std::cout << "line malformed" << std::endl;
	}
	tempString = "";
	record.clear();
}
void SetIO::allToSets(std::string &name){
	clearSet();
	openI(name);
	std::string item;
	int count;
	while (!input.eof){
		count = 1;
		item = "";
		obtainLine(item, count);
		addToSet(item, count);
	}
	closeI();
}
void SetIO::unionToSets(std::string &name){
	openI(name);
	std::string item;
	int count;
	while (!input.eof){
		count = 1;
		item = "";
		obtainLine(item, count);
		for (int i = 0; i < counter; i++){
			if (item == setList[i]){
				setCount[i] += count;
				i = counter;
				break;
			}
			else if (i + 1 == counter){
				addToSet(item, count);
			}
		}
	}
	closeI();
}
void SetIO::subtractFromSets(std::string &name){
	openI(name);
	std::string item;
	int count;
	while (!input.eof){
		count = 1;
		item = "";
		obtainLine(item, count);
		for (int i = 0; i < counter; i++){
			if (item == setList[i]){
				setCount[i] -= count;
				if (setCount[i] < 0){
					rmFromSet(i);
				}
			}
		}
	}
	closeI();
}

void SetIO::differenceFromSets(std::string &name){
	openI(name);
	std::string item;
	int count;
	while (!input.eof){
		count = 1;
		item = "";
		obtainLine(item, count);
		for (int i = 0; i < counter; i++){
			if (item == setList[i]){
				setCount[i] -= count;
				if (setCount[i] < 0){
					rmFromSet(i);
				}
				break;
			}
			else if (i + 1 == counter){
				addToSet(item, count);
			}
		}
	}
	closeI();
}

void SetIO::intersectionFromSets(std::string &name){
	openI(name);
	std::string item;
	int count;
	int tempCounter = counter;
	bool found;
	for (int i = tempCounter; i > 0; i--){
		found = false;
		while (!input.eof){
			count = 1;
			item = "";
			obtainLine(item, count);
			if (item == setList[i]){
				if (setCount[i] < count)
					setCount[i] = count;
				found = true;
			}
		}
		if (found == false){
			rmFromSet(i);
		}
		input.clear();
		input.seekg(0, std::ios::beg);
	}
	closeI();
}
void SetIO::outputSet(std::string &name){
	std::string tempString = name + ".txt";
	output.open(tempString.c_str());
	for (int i = 0; i <= counter; i++){
		output << setList[i] << " " << setCount[i] << std::endl;
	}g
	output.close();
	output.clear();
}

void SetIO::findItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index != -1){
		count = index;
		std::cout << "item " << item << " found with count " << setCount[index] << std::endl;
	}
	else
		std::cout << "item " << item << " not found" << std::endl; 
}

void SetIO::insertItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index == -1){
		addToSet(item, count);
	}
	else
		setCount[index] += count;
}

void SetIO::deleteItem(std::string &item){
	int index = findInSet(item);
	if (index != -1){
		rmFromSet(index);
		std::cout << "item " << item << " deleted " << std::endl;
	}
	else
		std::cout << "item " << item << " not in multiset" << std::endl;
}

void SetIO::reduceItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index != -1){
		if (setCount[index] > count){
			setCount[index] -= count;
			std::cout << "item " << item << " reduced to " << setCount[index] << std::endl;
		}
		else{
			rmFromSet(index);
			std::cout << "item " << item << " deleted " << std::endl;
		}
	}
	else
		std::cout << "item " << item << " not in multiset" << std::endl;
}



