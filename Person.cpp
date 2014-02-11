
#include <string>
#include "Person.h"
#include <iostream>
#include <sstream>
using namespace std;



Person::Person()
{
	first = "John";
	last = "Doe";
	age = 0;
	friendCap = 0;
	friendList = new Person*[friendCap];	
}

Person::Person(string first, string last, int age, int friendCap)
{
	this->first = first;
	this->last = last;
	this->age = age;
	this->friendCap = friendCap;
	friendList = new Person*[friendCap];
	
	for (int i = 0; i < friendCap; i++)
	{
		friendList[i] = NULL;
	}
	
}
string Person::toSimpleString()
{
	ostringstream ss;
	ss << first << " " << last << ", Age" << age;
	return ss.str();
}

bool Person::add(Person * p)
{
	if (p->isCapped() == true)
		return false;

	else
	{
		for (int i = 0; i < friendCap; i++)
		{
			if (friendList[i] == NULL)
			{
				friendList[i] = p;
				return true;
			}
			else
			{
				return false; //get back to this, it needs exception handling.
			}
		}
	}
	cout << "it shouldn't have made it this far;";
	return false;
}
string Person::toFullString()
{
	/*
	string allFriends;
	for(int i = 0; i< friendCap; i++)
	{
	allFriends += "\t" + friendList[i]->toSimpleString() + "\n";
	}
	string str = toSimpleString() +
	"\n Friends:"
	"\n" + allFriends;
	
	THIS ISNT DONE YET.
	*/
	ostringstream fs;
	fs << first << " " << last << ", Age" << age;
	return fs.str();

}
string Person::getFirstName()
{
	return first;
}
string Person::getLastName()
{
	return last;
}
int Person::getAge()
{
	return age;
}
int Person::getFriendCap()
{
	return friendCap;
}

Person** Person::getFriendList(int &size)
{
	size = friendCap;
	return friendList;

}
bool Person::isCapped()
{
	for (int i = 0; i < friendCap; i++)
	{
		if (friendList[i] == NULL)
		{
			i = friendCap;
			return false;
		}
		else{
			return true;
		}
	}
	cout << "it should not have made it this far";
	return false;
}

Person** Person::getUncappedFriends(int &size)
{


}
