#include <iostream>
#include <fstream>
#include <string>
#include "Project1.h"
#include <exception>

std::string setList[100];
int counter;
std::ifstream input;
std::ofstream output;

SetIO::SetIO(){
	counter = 0;
	for (int i = 0; i < 100; i++){
		setList[i] = "";
	}
}
void SetIO::addToSet(std::string &str){
	if (findInSet(str) == -1){
		counter++;
		setList[counter] = str;
	}
}

void SetIO::rmFromSet(int index){
	setList[index] = "";
}
int SetIO::findInSet(std::string &str){
	int pos = -1;
	for (int i = 0; i < counter; i++){
		if (setList[i] == str){
			pos = i;
		}
	}
	return pos;
}
void SetIO::clearSet(){
	for (int i = 0; i < 100; i++){
		setList[i] = "";
	}
	counter = 0;
}
void SetIO::openI(std::string &name){
	name += ".txt";
	input.open(name.c_str());
	if (input.fail())
		std::cout << "Unable to open file: " << name << std::endl;
}
void SetIO::openO(std::string &name){
	name += ".txt";
	output.open(name.c_str());

}
void SetIO::closeI(){
	input.close();
	input.clear();
}
void SetIO::closeO(){
	output.close();
	output.clear();
}


int main(){
	bool VERBOSE = true;
	bool NORMAL = false;
	bool SILENT = false;

	std::string stringFile;
	int select = 20;
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

			std::cin >> select;
			if (std::cin.fail()){
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Int Exception!" << std::endl;
			}
		
		if (select == 1 || select == 2 || select == 3 || select == 4 || select == 5 || select == 7 || select == 9 || select == 10 || select == 11){
				std::cin >> stringFile;				
		}
		else if (select == 6 || select == 8 || select == 12 || select == 13 || select == 14 || select == 15 || select == 0){}
		else if (select > 15 || select < 0 || select == 20){
			std::cout << "Command is invalid" << std::endl;
		}
		if (select == 0){}
		else if (select == 1){		//input a file
			std::string tempString;
			
			setIO.openI(stringFile);
			if (!setIO.input.fail()){
				setIO.clearSet();
				if (!SILENT)
					std::cout << "New set loaded" << std::endl;
				while (!setIO.input.eof()){
					std::getline(setIO.input, tempString);
					setIO.addToSet(tempString);
				}


				setIO.closeI();
			}
		}
		else if (select == 2){		//union of two files into a set
			std::string tempString;
			setIO.openI(stringFile);
			if (!setIO.input.fail()){
				if (!SILENT)
					std::cout << "Union completed" << std::endl;
				while (!setIO.input.eof()){
					std::getline(setIO.input, tempString);
					setIO.addToSet(tempString);
				}


				setIO.closeI();
			}
		}
		else if (select == 3){		//subtraction of file from current set
			std::string tempString;
			setIO.openI(stringFile);
			if (!setIO.input.fail()){
				if (!SILENT)
					std::cout << "Subtraction completed" << std::endl;
				while (!setIO.input.eof()){
					std::getline(setIO.input, tempString);
					for (int i = 0; i <= setIO.counter; i++){
						if (tempString == setIO.setList[i]){
							setIO.rmFromSet(i);
						}
					}
				}


				setIO.closeI();
			}
		}
		else if (select == 4){		//difference of file and set
			std::string tempString;
			setIO.openI(stringFile);
			if (!setIO.input.fail()){
				if (!SILENT)
					std::cout << "Difference completed" << std::endl;
				while (!setIO.input.eof()){
					int addToFile = 0;
					std::getline(setIO.input, tempString);
					for (int i = 0; i <= setIO.counter; i++){
						if (tempString == setIO.setList[i]){
							setIO.rmFromSet(i);
							addToFile = i;
						}
					}
					if (addToFile == 0){
						setIO.addToSet(tempString);
					}
				}



				setIO.closeI();
			}
		}
		else if (select == 5){		//intersection of file and set
			std::string tempString;
			setIO.openI(stringFile);
			if (!setIO.input.fail()){
				if (!SILENT)
					std::cout << "Intersection completed" << std::endl;
				for (int i = 0; i <= setIO.counter; i++){
					int rm = -1;


					while (!setIO.input.eof()){
						std::getline(setIO.input, tempString);
						if (tempString == setIO.setList[i])
							rm = i;

					}

					if (rm == -1){
						setIO.rmFromSet(i);
					}
					setIO.input.clear();
					setIO.input.seekg(0, std::ios::beg);
				}


				setIO.closeI();
			}
		}
		else if (select == 6){		//reset set
			setIO.clearSet();
			if (!SILENT)
				std::cout << "Reset completed" << std::endl;
		}
		else if (select == 7){		//output a set
			std::string outputFile = "./" + stringFile;
			setIO.openO(outputFile);
			if (!setIO.output.fail()){
				if (!SILENT)
					std::cout << "save to " << stringFile << " completed" << std::endl;
				for (int i = 0; i <= setIO.counter; i++){
					if (setIO.setList[i] != "")
						setIO.output << setIO.setList[i] << std::endl;
				}
			}
			else
				std::cout << "Error with output name, try another?" << std::endl;
			setIO.closeO();
		}
		else if (select == 8){		//print set
			for (int i = 0; i <= setIO.counter; i++){
				if (setIO.setList[i] != "")
					std::cout << setIO.setList[i] << std::endl;
			}

		}
		else if (select == 9){		//find item in set
			std::string con;
			con = "not ";
			for (int i = 0; i <= setIO.counter; i++){
				if (stringFile == setIO.setList[i]){
					con = "";
				}
			}
			if (!SILENT)
				std::cout << "Item " << stringFile << " " << con << "found" << std::endl;
		}
		else if (select == 10) {
			setIO.addToSet(stringFile);
			if (!SILENT)
				std::cout << "Item " << stringFile << " inserted" << std::endl;
		}
		else if (select == 11){
			if (setIO.findInSet(stringFile) != -1){
				setIO.rmFromSet(setIO.findInSet(stringFile));
			}
			if (!SILENT)
				std::cout << "Item " << stringFile << " deleted" << std::endl;
		}
		else if (select == 12){		//verbose mode
			VERBOSE = true;
			SILENT = false;
			NORMAL = false;
		}
		else if (select == 13){		//normal mode
			VERBOSE = false;
			SILENT = false;
			NORMAL = true;
		}
		else if (select == 14){		//silent mode
			VERBOSE = false;
			SILENT = true;
			NORMAL = false;
		}
		else if (select == 15){		//print to screen the help.
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