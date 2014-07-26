#include <iostream>
#include "DynamicArray.h"
#include <string>
DynamicArray::DynamicArray(){
	DA = new std::string[5];
	SIZE = 0;
	CAPACITY = 5;
}
DynamicArray::DynamicArray(int capacity){
	DA = new std::string[capacity];
	SIZE = 0;
	CAPACITY = capacity;
}
DynamicArray::~DynamicArray(){
	delete [] DA;
	DA = NULL;
	SIZE = 0;
	CAPACITY = 0;
}
bool DynamicArray::insert(std::string str){
	if(SIZE == CAPACITY){
		grow();
	}
	if(SIZE < CAPACITY){
		DA[SIZE] = str;
		SIZE++;
		return true;
	}
	else{
		std::cerr << "something went wrong" << std::endl;
		return false;
	}
}
std::string DynamicArray::remove(){
	SIZE--;
	std::string str = DA[SIZE];
	return str;
}
std::string DynamicArray::remove(int index){
	std::string AtIndex = "";
	if(index < SIZE && index >= 0){
		AtIndex = *(DA + index);
		for(int i = index;i < SIZE;i++){
			DA[i] = DA[i +1];
		}
		SIZE--;
	}
	return AtIndex;
}
void DynamicArray::remove(std::string str){
	int found = index_of(str);
	if(found != -1){
		remove(found);
	}
}
int DynamicArray::index_of(std::string str){
	int found = -1;
	for(int i = 0; i < SIZE; i++){
		if(*(DA + i) == str)
			found = i;
	}
	return found;
}
std::string DynamicArray::item_at(int index){
	if(index < SIZE && index >= 0){
		return *(DA + index);
	}
	else{
		return "";
	}
}
int DynamicArray::size(){
	return SIZE;
}
int DynamicArray::capacity(){
	return CAPACITY;
}
void DynamicArray::clear(){
	SIZE = 0;
}
void DynamicArray::grow(){
	CAPACITY = CAPACITY * 2;
	std::string * NewDA = new std::string[CAPACITY];
	for(int i = 0;i < SIZE; i++){
		*(NewDA + i) = *(DA + i);
	}
	delete [] DA;
	DA = NewDA;
	NewDA = NULL;
}
int DynamicArray::get_size() const{
	return SIZE;
}
int DynamicArray::get_capacity() const{
	return CAPACITY;
}
std::string DynamicArray::get_item(int index) const{
	std::string str = "";
	if(index < SIZE){
		str = DA[index];
	}
	return str;
}
DynamicArray & DynamicArray::operator=(const DynamicArray & rhs){
	if(this != &rhs){
		delete [] DA;
		this->SIZE = 0;
		this->CAPACITY = 5;
		this->DA = new std::string[rhs.get_capacity()];
		for(int i = 0; i < rhs.get_size();i++)
			this->insert(rhs.get_item(i));
	}
	return *this;
}

const DynamicArray DynamicArray::operator+(const DynamicArray & rhs) const{
	DynamicArray temp;
	for(int i = 0;i < this->SIZE;i++){
		temp.insert(this->get_item(i));
	}
	for(int j = 0;j < rhs.get_size();j++){
		temp.insert(rhs.get_item(j));
	}
	return temp;
}

std::string & DynamicArray::operator[](const int index){
	if(index < this->SIZE){
		return *(this->DA + index);
	}
}

std::ostream &operator<<(std::ostream &os, const DynamicArray rhs){
	
	if(rhs.get_size() > 0)
		os << "[" << rhs.get_item(0);
	if(rhs.get_size() > 1){
		for(int i = 1;i < rhs.get_size();i++){

			os << ", " << rhs.get_item(i);
		}
	}
	if(rhs.get_size() > 0){
		os << "]";
	}
	return os;
}
