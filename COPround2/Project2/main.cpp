#include <string>
#include "Project2.h"
#include <iostream>
#include <sstream>

int main( int argc, char *argv[] ){
	bool VERBOSE = false;
	bool NORMAL = true;
	bool SILENT = false;

	std::string stringFile;
	int select = 20;
	int number = 1;
	std::string line;
	SetIO setIO;
	char a = '9';
	char b = 'A';
	int c = a;
	int d = b;
	bool fromCLine = false;
	for(int i = 0;i < argc; i++){
		if(argv[i] == "-s"){
			SILENT = true;
			NORMAL = false;
		}
		if(argv[i] == "-v"){
			VERBOSE = true;
			NORMAL = false;
		}
		if(argv[i] == "-h"){
			setIO.help();
		}
		if(argv[i] == "-f"){
			stringFile = argv[i+1];

			fromCLine = true;
		}
	}
	while (select != 0){
		if (VERBOSE){
			std::cout << "0 - exit; 1 - input <file>; 2 - union <file>; 3 - subtract <file>;\n" <<
				"4 - difference <file>; 5 - intersect <file>; 6 - reset current set;\n" <<
				"7 - write <file>; 8 - print; 9 - find <item>; 10 - insert <item> <count>;\n" <<
				"11 - delete <item>; 12 - reduce <item> <count> ;13 - verbose; 14 - normal; 15 - silent; 16 - help" << std::endl;
		}
		if (!SILENT){
			std::cout << "> ";
		}
		if(fromCLine == false){
			getline(std::cin, line);
			std::istringstream record(line);

			record >> select;
			if (!record.eof()){
				record >> stringFile;
				int check = stringFile.at(0);
				if (check <= 57){
					select = std::stoi(stringFile.c_str());
					if (!record.eof())
						record >> stringFile;

				}
				if (!record.eof()){
					record >> number;
					if (record.fail()){
						std::cerr << "Item <stringFile><count> is not in correct format on user input line" << std::endl;
						select = 16;
					}
				}

			}
			line = "";
		}
		else
			fromCLine = false;
		if (select > 15 || select < 0 || select == 20){
			std::cerr << "Command is invalid" << std::endl;		//NUMBER 4 ERROR
		}
		
		if (select == 0){}
		else if (select == 1){		//input a file
			int result = setIO.allToSets(stringFile,VERBOSE);
			if (!SILENT && result == 0){
				
				std::cout << "New set loaded ";
				if (VERBOSE)
					std::cout << "from " << stringFile << std::endl;
				else
					std::cout << std::endl;
			}
			
		}
		else if (select == 2){		//union of two files into a set
			
			if (!SILENT && setIO.unionToSets(stringFile, VERBOSE) == 0)
				std::cout << stringFile << " union completed" << std::endl;
		}
		else if (select == 3){		//subtraction of file from current set
			if (!SILENT && setIO.subtractFromSets(stringFile, VERBOSE) == 0)
				std::cout << stringFile << " subtraction completed" << std::endl;
		}
		else if (select == 4){		//difference of file and set
			
			if (!SILENT && setIO.differenceFromSets(stringFile, VERBOSE) == 0)
				std::cout << stringFile << " difference completed" << std::endl;

		}
		else if (select == 5){		//intersection of file and set
			
			if (!SILENT && setIO.intersectionFromSets(stringFile, VERBOSE) == 0)
				std::cout << stringFile << " intersection completed" << std::endl;
		}
		else if (select == 6){		//reset set
			setIO.clearSet();
			if (!SILENT)
				std::cout << "Reset completed" << std::endl;
		}
		else if (select == 7){		//output a set
			
			if (!SILENT && setIO.outputSet(stringFile) == 0)
				std::cout << "save to " << stringFile << " completed" << std::endl;
			else
				std::cerr << "File " << stringFile << " doesn not exist or exists but cannot be opened in the desired mode." << std::endl;
		}
		else if (select == 8){		//print set
			
			if (!SILENT)
				std::cout << "Current set:" << std::endl;

			setIO.printList();

		}
		else if (select == 9){		//find item in set
			int count = 0;
			int result = setIO.findItem(stringFile, count);
			if (!SILENT && result == 0){
				std::cout << "Item " << stringFile << " found with count " << count << std::endl;
			}
			else if (result == 1)
				std::cout << "item " << stringFile << " not in set" << std::endl;
				
		}
		else if (select == 10) {
			setIO.insertItem(stringFile, number);
			if (!SILENT)
				std::cout << "Item " << stringFile << " inserted with count " << number << std::endl;
		}
		else if (select == 11){
			int result = setIO.deleteItem(stringFile);
			if (!SILENT && result == 0)
				std::cout << "Item " << stringFile << " deleted" << std::endl;
			else if (result == 1)
				std::cout << "item " << stringFile << " not in multiset" << std::endl;
		}
		else if (select == 12){	//reduce item by count
			int result = setIO.reduceItem(stringFile, number);
			if(!SILENT && result == 0)
				std::cout << "Item " << stringFile << " count reduced to " << number << std::endl;
			else if (!SILENT && result == 1)
				std::cout << "item " << stringFile << " removed " << std::endl;
			else if (result == 2)
				std::cout << "item " << stringFile << " not in multiset" << std::endl;
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
			setIO.help();
		}
	}
	return 0;
};

/*NOTE:
This program is not capable of handling having a set with more than 100 items, and will not reorganize items (and therefore lower the counter) even if items are removed. The only way to deal with this
is to use setIO.clearSet(), which will remove all of the items and reset the counter to zero.
*/