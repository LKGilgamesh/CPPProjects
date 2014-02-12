
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
    //this is done.
}

Person::Person(string first1, string last1, int age1, int friendCap1)
{
	first = first1;
	last = last1;
	age = age1;
	friendCap = friendCap1;
	friendList = new Person*[friendCap];

	for (int i = 0; i < friendCap; i++)
	{
		friendList[i] = NULL;
	}
    //this is done
}
Person::~Person()
{
    //i need to find out how to do this.
    delete(friendList);
}
string Person::toSimpleString()
{
    ostringstream ss;
	ss << first << " " << last << ", Age" << age;
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
	string fs1 = toSimpleString();
	string fs2 = "\n Friends: \n";
    string ffs = fs1 + fs2;

    for(int i = 0; i< friendCap; i++)
	{
        ffs += string("\t") + friendList[i]->toSimpleString() + string("\n");
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
    int unCappedSize;
    int index;
    Person** unCappedFriendList;
    for(int i = 0;i < friendCap;i++)
    {
        if(friendList[i]->isCapped() == false)
        {
            unCappedSize++;
        }
    }
    unCappedFriendList = new Person*[unCappedSize];

    for(int j = 0;j < friendCap; j++)
    {
        if(friendList[j]->isCapped() == false)
        {
            unCappedFriendList[index] = friendList[j];
            index++;
        }
    }
    return unCappedFriendList;
}
