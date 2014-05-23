#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
public:
	Person(string first, string last, int age, int friendCap);
	Person();
	~Person();

	bool add(Person* p);
	string toSimpleString();
	string toFullString();
	string getFirstName();
	string getLastName();
	int getAge();
	int getFriendCap();
	Person** getFriendList(int& size);
	bool isCapped();
	Person** getUncappedFriends(int& size);



	/*
	* Define any desired "helper functions" here.
	*/

private:
	string first, last;
	int age, friendCap, numOfFriends;
	Person **friendList;
	/*
	* Define any necessary fields here.
	*/
};

#endif // P
