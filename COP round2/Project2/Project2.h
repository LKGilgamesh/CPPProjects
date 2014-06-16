#ifndef PROJECT2_H
#define PROJECT2_H

#include<string>
#include<fstream>
#include<vector>

class SetIO{
private:
	std::vector<std::string> setList;
	std::vector<int> setCount;
	int counter;
public:
	SetIO();
	std::ifstream input;
	std::ofstream output;
	void addToSet(std::string &str,int & number);
	void rmFromSet(int index);
	int findInSet(std::string &str);
	void clearSet();
	void printList();
	void openI(std::string &name);
	void closeI();
	void obtainLine(std::string &item,int &count);
	void allToSets(std::string &name);
	void unionToSets(std::string &name);
	void subtractFromSets(std::string &name);
	void differenceFromSets(std::string &name);
	void intersectionFromSets(std::string &name);
	void outputSet(std::string &name);
	void findItem(std::string &item,int &count);
	void insertItem(std::string &item, int &count);
	void deleteItem(std::string &item);
	void reduceItem(std::string &item,int &count);
};

#endif // P