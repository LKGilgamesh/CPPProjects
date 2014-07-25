#include "group.h"
#include <string>
#include <iostream>
using namespace std;

void menu();
int get_input();
void get_insert(string &, int &);
void get_delete(string &);

int main(){
    group Group;
    int choice = -1;
    string temp_name;
    int temp_age;
    while(choice){
        cout << endl;
        menu();
        choice = get_input();
        cout << endl;
        if(choice == 1){
            get_insert(temp_name, temp_age);
            int success = Group.insert_person(temp_name, temp_age);
            if(success)
                cout << temp_name << " inserted successfully" << endl;
            else
                cout << "Error inserting " << temp_name << endl;
        }
        else if(choice == 2){
            get_delete(temp_name);
            int success = Group.delete_person(temp_name);
            if(success)
                cout << temp_name << " deleted successfully" << endl;
            else
                cout << "Error deleting " << temp_name << endl;
        }
        else if(choice == 3){
            Group.print_people();
        }
    }

    return 0;
}

void menu(){
    cout << "1. Add person" << endl;
    cout << "2. Delete Person" << endl;
    cout << "3. Print list" << endl;
    cout << "0. Exit" << endl;
    cout << endl << "> " << flush;
}

int get_input(){
    int input;
    cin >> input;
    return input;
}

void get_insert(string & name, int & age){
    cin >> name;
    cin >> age;
}

void get_delete(string & name){
    cin >> name;
}