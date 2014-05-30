#ifndef PROJECT1_H
#define PROJECT1_H

#include<string>
#include<fstream>

class SetIO{
public:
	SetIO();

	std::string setList[100];
	int counter;
	std::ifstream input;
	std::ofstream output;
	void addToSet(std::string &str);
	void rmFromSet(int index);
	int findInSet(std::string &str);
	void clearSet();
	void openI(std::string &name);
	void openO(std::string &name);
	void closeI();
	void closeO();
};

#endif // P