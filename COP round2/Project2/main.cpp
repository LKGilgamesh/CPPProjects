#include <string>
#include "Project2.h"
#include <iostream>
#include <sstream>

int main(){
	bool VERBOSE = true;
	bool NORMAL = false;
	bool SILENT = false;

	std::string stringFile;
	int select = 20;
	int number = 1;
	std::string line;
	SetIO setIO;
	while (select != 0){
		if (VERBOSE){
			std::cout << "0 - exit; 1 - input <file>; 2 - union <file>; 3 - subtract <file>;\n" <<
				"4 - difference <file>; 5 - intersect <file>; 6 - reset current set;\n" <<
				"7 - write <file>; 8 - print; 9 - find <item>; 10 - insert <item>;\n" <<
				"11 - delete <item>; 12 - verbose; 13 - normal; 14 - silent; 15 - help" << std::endl;
		}
		if (!SILENT){
			std::cout << "> ";
		}
		while (getline(std::cin, line)){
			std::istringstream record(line);
			record >> select >> stringFile >> number;
			bool read_fail = false;
			if (read_fail = record.fail()){
				std::cout << "input failure" << std::endl;
			}
		}

		/*
		std::cin >> select;
		if (std::cin.fail()){
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Int Exception!" << std::endl;
		}

		if (select == 1 || select == 2 || select == 3 || select == 4 || select == 5 || select == 7 || select == 9|| select == 11){
			std::cin >> stringFile;

		}
		else if (select == 6 || select == 8 || select == 13 || select == 14 || select == 15 || select == 16 || select == 0){}
		else if (select == 10 || select == 12){

		}
		else if (select > 15 || select < 0 || select == 20){
			std::cout << "Command is invalid" << std::endl;
		}
		*/
		if (select == 0){}
		else if (select == 1){		//input a file
			setIO.allToSets(stringFile);
			if (!SILENT)
				std::cout << "New set loaded" << std::endl;

		}
		else if (select == 2){		//union of two files into a set
			setIO.unionToSets(stringFile);
			if (!SILENT)
				std::cout << "Union completed" << std::endl;
		}
		else if (select == 3){		//subtraction of file from current set
			setIO.subtractFromSets(stringFile);
			if (!SILENT)
				std::cout << "Subtraction completed" << std::endl;
		}
		else if (select == 4){		//difference of file and set
			setIO.differenceFromSets(stringFile);
			if (!SILENT)
				std::cout << "Difference completed" << std::endl;

		}
		else if (select == 5){		//intersection of file and set
			setIO.intersectionFromSets(stringFile);
			if (!SILENT)
				std::cout << "Intersection completed" << std::endl;
		}
		else if (select == 6){		//reset set
			setIO.clearSet();
			if (!SILENT)
				std::cout << "Reset completed" << std::endl;
		}
		else if (select == 7){		//output a set
			setIO.outputSet(stringFile);
			if (!SILENT)
				std::cout << "save to " << stringFile << " completed" << std::endl;
		}
		else if (select == 8){		//print set
			setIO.printList();

		}
		else if (select == 9){		//find item in set
			int count = 0;
			setIO.findItem(stringFile, count);
			if (!SILENT){}
				
		}
		else if (select == 10) {
			setIO.insertItem(stringFile, number);
			if (!SILENT)
				std::cout << "Item " << stringFile << " inserted" << std::endl;
		}
		else if (select == 11){
			setIO.deleteItem(stringFile);
			if (!SILENT)
				std::cout << "Item " << stringFile << " deleted" << std::endl;
		}
		else if (select == 12){	//reduce item by count
			setIO.reduceItem(stringFile, number);
		}
		else if (select == 13){		//verbose mode
			VERBOSE = true;
			SILENT = false;
			NORMAL = false;
		}
		else if (select == 14){		//normal mode
			VERBOSE = false;
			SILENT = false;
			NORMAL = true;
		}
		else if (select == 15){		//silent mode
			VERBOSE = false;
			SILENT = true;
			NORMAL = false;
		}
		else if (select == 16){		//print to screen the help.
			std::cout << "== == == == == == == == == == == == == == == == == == == == == == == == == == ==\n" <<
				"The numbered commands are as follows :\n0. exit\n1. input file <filename> : open and read a list from a file to the current list\n" <<
				"2. union file <filename> : open and union a set from a file with the current set" <<
				"3. subtract file <filename> : open and subtract set from a file from the current set\n" <<
				"4. difference file <filename> : open and find the difference between a set from a file and the current set\n" <<
				"5. intersect file <filename> : open and find the intersection between a set from a file and the current set\n" <<
				"6. reset current set to the empty set\n7. output file <filename> : open and write the current set to a file\n" <<
				"8. print current set to the console\n9. find <item name> : test if <item name> is in the current set\n" <<
				"10. insert <item name> : add <item name> to the current set if it is not already in it\n11. delete <item name> : remove <item name> from the current set if it is in it\n" <<
				"12. verbose output\n13. normal output\n14. silent output\n15. help\n" <<
				"== == == == == == == == == == == == == == == == == == == == == == == == == == ==" << std::endl;

		}
	}
	return 0;
};

/*NOTE:
This program is not capable of handling having a set with more than 100 items, and will not reorganize items (and therefore lower the counter) even if items are removed. The only way to deal with this
is to use setIO.clearSet(), which will remove all of the items and reset the counter to zero.
*/