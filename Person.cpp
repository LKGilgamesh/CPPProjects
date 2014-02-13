
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

	for (int i = 0; i < friendCap; i++)
	{
		friendList[i] = NULL;
	}
	numOfFriends = 0;
	//this is done.
}

Person::Person(string first, string last, int age, int friendCap)
{
	this->first = first;
	this->last = last;
	
	if (age <= 0)
	{
		throw out_of_range("Age can't be 0 or negative");
	}
	this->age = age;

	if (friendCap < 0)
	{
		throw out_of_range("friendCap can't be negative");
	}

	this->friendCap = friendCap;
	friendList = new Person*[friendCap];

	for (int i = 0; i < friendCap; i++)
	{
		friendList[i] = NULL;
	}
	numOfFriends = 0;
	//this is done
}

Person::~Person(){};

string Person::toSimpleString()
{
	ostringstream ss;
	ss << "<" << first << "> <" << last << ">, Age <" << age << ">";
	return ss.str();
	//this is done
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
				i = friendCap;
				numOfFriends++;
				return true;
			}
		}
	}
	return false;
}
string Person::toFullString()
{
	string fs1 = toSimpleString();
	string fs2 = "\n Friends: \n";
	string ffs = fs1 + fs2;

	for (int i = 0; i< friendCap; i++)
	{
		if (friendList[i] != NULL)
		{
			ffs += string("\t") + friendList[i]->toSimpleString() + string("\n");
		}
	}

	//this may work, will need to test.
	return ffs;
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
	size = numOfFriends;
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
	}
	//cout << "it should not have made it this far";
	return true;
}

Person** Person::getUncappedFriends(int &size)
{
	int index = 0; //will give the size of the new array
	int location = 0; //will determine the location of the array as Persons are put into it
	Person** unCappedFriendList;
	for (int i = 0; i < friendCap; i++)
	{
		if (friendList[i] != NULL && friendList[i]->isCapped() == false)
		{
			index++;
		}
	}
	unCappedFriendList = new Person*[index];
	for (int k = 0; k < friendCap; k++)
	{
		unCappedFriendList[k] = NULL;
	}
	for (int j = 0; j < friendCap; j++)
	{
		if (friendList[j] != NULL && friendList[j]->isCapped() == false)
		{
			unCappedFriendList[location] = friendList[j];
			location++;
		}

	}
	size = index;
	return unCappedFriendList;
}
