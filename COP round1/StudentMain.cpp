#include "Person.h"
#include <iostream>
#include <stdexcept>

int main()
{
	Person* pm = new Person("Peyton","Manning",37,3);
	Person* al = new Person("Andrew","Luck",24,4);
	Person* ck = new Person("Colin","Kaepernick",26,4);
	Person* db = new Person("Drew","Brees",35,4);
	Person* tb = new Person("Tom","Brady",36,4);

	pm->add(al);
	al->add(pm);
	al->add(db);
	al->add(tb);
	al->add(ck);

	cout<<pm->toFullString()<<endl<<endl;

	int list1Size,list2Size;

	Person** list1=pm->getFriendList(list1Size);

	cout<<list1[0]->toFullString()<<endl<<endl;

	for(int i=0; i<list1Size; i++)
	{
		Person** list2=list1[i]->getUncappedFriends(list2Size);

		for(int j=0; j<list2Size; j++)
		{
			pm->add(list2[j]);
		}
		delete[] list2;
	}

	cout<<pm->toFullString()<<endl<<endl;
	
	Person* empty = 0;
	try
	{
		empty=new Person("","",-4,5);
	}
	catch(exception &e)
	{
		cout<<e.what()<<endl;
	}
	
	delete[] list1;

	delete pm;
	delete al;
	delete ck;
	delete db;
	delete tb;

	if(empty != 0)
		delete empty;


	return 0;
}
