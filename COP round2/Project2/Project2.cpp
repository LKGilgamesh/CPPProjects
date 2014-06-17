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
	counter = 0;
}
void SetIO::printList(){
	for (int i = 0; i < counter; i++){
		std::cout << setList[i] << " " << setCount[i] << std::endl;
	}
}
void SetIO::openI(std::string &name){
	std::string tempName = "./" + name + ".txt";
	input.open(tempName.c_str());
	if (input.fail())
		std::cerr << "Unable to open file: " << name << std::endl;
}

void SetIO::closeI(){
	input.close();
	input.clear();
}
int SetIO::obtainLine(std::string &item, int &count, bool &mode){
	std::string tempString;
	getline(input, tempString);
	std::istringstream record(tempString);
	record >> item >> count;
	record >> tempString;
	if (!record.eof()){
		std::cerr << "File is not in correct format" << std::endl;
		if (mode)
			std::cout << "Line " << tempString << "is incorrect" << std::endl;
		return 1;
	}
	tempString = "";
	record.clear();
	return 0;
}
int SetIO::allToSets(std::string &name, bool &mode){
	clearSet();
	openI(name);
	std::string item;
	int count;
	if (!input.fail()){
		while (!input.eof()){
			count = 1;
			item = "";
			obtainLine(item, count, mode);
			addToSet(item, count);
		}
		closeI();
		return 0;
	}
	else{
		return 1;
	}
}
int SetIO::unionToSets(std::string &name, bool &mode){
	openI(name);
	std::string item;
	int count;
	if (!input.fail()){
		while (!input.eof()){

			count = 1;
			item = "";
			int result = obtainLine(item, count, mode);
			if (result == 1)
				break;
			bool isThere = false;
			for (int i = 0; i < counter; i++){
				if (item == setList[i]){
					setCount[i] += count;
					i = counter;
					isThere = true;
					break;
				}
			}
			if (isThere == false)
				addToSet(item, count);
		}
		closeI();
		return 0;
	}
	else
		return 1;
	
}
int SetIO::subtractFromSets(std::string &name, bool &mode){
	openI(name);
	std::string item;
	int count;
	if (!input.fail()){
		while (!input.eof()){
			count = 1;
			item = "";
			obtainLine(item, count, mode);
			for (int i = 0; i < counter; i++){
				if (item == setList[i]){
					setCount[i] -= count;
					if (setCount[i] <= 0){
						rmFromSet(i);
					}
				}
			}
		}
		closeI();
		return 0;
	}
	else
		return 1;
}

int SetIO::differenceFromSets(std::string &name, bool &mode){
	openI(name);
	std::string item;
	int count;
	if (!input.fail()){
		while (!input.eof()){
			count = 1;
			item = "";
			obtainLine(item, count, mode);
			bool isThere = false;
			for (int i = 0; i < counter; i++){
				if (item == setList[i]){
					if (setCount[i] < count)
						setCount[i] = count - setCount[1];
					else if (setCount[i] > count)
						setCount[i] = setCount[i] - count;
					else
						rmFromSet(i);
					isThere = true;
					break;
				}
			}
			if (isThere == false)
				addToSet(item, count);
		}
		closeI();
		return 0;
	}
	else
		return 1;
}

int SetIO::intersectionFromSets(std::string &name, bool &mode){
	openI(name);
	std::string item;
	int count;
	int tempCounter = counter - 1;
	bool found;
	if (!input.fail()){
		for (int i = tempCounter; i >= 0; i--){
			found = false;
			while (!input.eof()){
				count = 1;
				item = "";
				obtainLine(item, count, mode);
				if (item == setList[i]){
					if (setCount[i] > count)
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
		return 0;
	}
	return 1;
}
int SetIO::outputSet(std::string &name){
	std::string tempString = name + ".txt";
	output.open(tempString.c_str());
	if (!output.fail()){
		for (int i = 0; i < counter; i++){
			output << setList[i] << " " << setCount[i] << std::endl;
		}
		output.close();
		output.clear();
		return 0;
	}
	else
		return 1;
}

int SetIO::findItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index != -1){
		count = setCount[index];
		return 0;
	}
	else
		return 1;

}

void SetIO::insertItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index == -1){
		addToSet(item, count);
	}
	else {
		setCount[index] += count;
	}

}

int SetIO::deleteItem(std::string &item){
	int index = findInSet(item);
	if (index != -1){
		rmFromSet(index);
		return 0;
	}
	else
		return 1;
		
}

int SetIO::reduceItem(std::string &item, int &count){
	int index = findInSet(item);
	if (index != -1){
		if (setCount[index] > count){
			setCount[index] -= count;
			count = setCount[index];

			return 0;
		}
		else{
			rmFromSet(index);
			count = 0;
			return 1;		
		}
	}
	else
		return 2;
		
}



