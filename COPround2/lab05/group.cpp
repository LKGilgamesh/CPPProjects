#include "group.h"
#include <string>
#include <iostream>

using namespace std;
person::person(){
    age=20;
    name="Leon";
}
person::person(int age,string name){
    this->age = age;
    this->name = name;
}
int person::getAge(){
    return age;
}
string person::getName(){
    return name;
}
void person::setAge(int age){
    if(age >0 && age < 200){
        this->age = age;
    }
    else 
        cout << "Incorrect Age." << endl;
}
void person::setName(string name){
    this->name = name;
}

group::group(){
    size = 0;
    for(int i = 0;i < GROUP_SIZE;i++){
        people[i] = person(0,"");
    }
}
int group::find_index(string name){
    int index = -1;
    for(int i=0;i<size; i++){
        if(people[i].getName() == name){
            index = i;
            i = size;
        }
    }
    return index;
}

int group::insert_person(string name, int age){
    // If our group is full, we cannot add anymore
    if(size == GROUP_SIZE) return 0;

    // Find where we need to insert the person
    int index = size;
    for(int i=0;i<size; i++){
        if(people[i].getName().compare(name) > 0){
            index = i;
            i = size;
        }
    }

    // Move everyone else down one space to make room
    for(int i=size;i>index;i--){
        people[i] = people[i-1];
    }

    // Insert the person
    people[index] = person(age,name);

    size++;
    return 1;
}

int group::delete_person(string name){
    // Check if the person is in the list
    int index = find_index(name);
    if(index == -1) return 0;

    // Move everyone lower than the one we are deleting 
    for(int i=index;i<size;i++){
        people[i] = people[i+1];
    }
    size--;

    return 1;
}

void group::print_people(){
    for(int i=0;i<size;i++){
        cout << people[i].getName() << ", " << people[i].getAge() << endl;
    }
}

