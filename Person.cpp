#include <string>
#include "Person.h"
using namespace std;



    Person::Person()
    {
        first = "John";
        last = "Doe";
        age = 19;
        friendCap = 10;
        Person * friendList[friendCap];
        for(int i = 0; i < friendCap; i++)
        {
            friendList[i] = NULL;
        }
    }
    Person::Person(string first, string last, int age, int friendCap)
    {
        this->first = first;
        this->last = last;
        this->age = age;
        this->friendCap = friendCap;
        Person * friendList[friendCap];
        for(int i = 0; i < friendCap; i++)
        {
            friendList[i] = NULL;
        }
    }
    string Person::toSimpleString()
    {
        //look up ssstream that shit below is all wrong.
        //string str = first + " " + last + ", Age" + age;
        return "poop";
    }

    bool Person::add(Person * p)
    {
        if(p->isCapped() == true)
            return false;

        else
        {
            for(int i = 0; i < friendCap; i++)
            {
                if(friendList[i] == NULL)
                {
                    friendList[i] = p;
                }
            }
        }
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
                     "\n" + allFriends;*/
        return "poop2";
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
    bool Person::isCapped()
    {
        for(int i = 0; i < friendCap; i++)
        {
            if(friendList[i] == NULL)
            {
                i = friendCap;
                return false;
            }
            else{
                return true;
            }
        }
    }
