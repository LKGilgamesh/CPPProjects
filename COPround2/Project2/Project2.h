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
	int obtainLine(std::string &item,int &count, bool &mode);
	int allToSets(std::string &name, bool &mode);
	int unionToSets(std::string &name, bool &mode);
	int subtractFromSets(std::string &name, bool &mode);
	int differenceFromSets(std::string &name, bool &mode);
	int intersectionFromSets(std::string &name, bool &mode);
	int outputSet(std::string &name);
	int findItem(std::string &item,int &count);
	void insertItem(std::string &item, int &count);
	int deleteItem(std::string &item);
	int reduceItem(std::string &item,int &count);
	void help();
};

#endif // P