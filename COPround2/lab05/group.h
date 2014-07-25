#ifndef GROUP_H
#define GROUP_H

#include <string>
using namespace std;
class person{
public:
	person();
	person(int age, string name);
	int getAge();
	string getName();
	void setAge(int age);
	void setName(string name);
private:
	int age;
	string name;
};
class group{
public:
	group();
	// This function inserts a person with the given name and age
	int insert_person(string, int);

	// This function deletes a person with the given age
	int delete_person(string);

	// This function prints out the people in our group
	void print_people();

	// This function returns the index of the given person. -1 on fail.
	// This is an auxillary function 
	int find_index(string name);
private:
	static const int GROUP_SIZE = 10;
	person people[GROUP_SIZE];
	int size;
};
#endif