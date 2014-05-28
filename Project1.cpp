#include <iostream>
#include <fstream>
#include <string>
#include <set>
std::string getFileName(){
	std::string name;
	std::cout << "What is the name of the file? -- " << std::flush;
	std::cin >> name;
	return name;
}
int main(){
	std::ifstream input;
	std::ofstream output;
	std::set<std::string> set1;
	int select=20;

	while (select != 0){
		std::cout << "0. exit\n1. input file\n2. union file\n3. subtract file\n4. difference file\n" <<
			"5. intersect file\n6. reset to empty set\n7. output file\n8. print set\n9. find\n" <<
			"10. insert\n11. delete\n12. verbose output\n13. normal output\n14. silent output\n15. help\n" << std::endl;
		std::cin >> select;
		if (select == 0){
			std::cout << "Goodbye." << std::endl;
		}
		else if (select == 1){		//input a file
			input.clear();
			set1.clear();
			std::string tempString;
			input.open(getFileName().c_str());
			while (!input.eof()){
				std::getline (input, tempString);
				set1.insert(tempString);
			}
			input.close();
		}
		else if (select == 2){		//union of two files into a set.
			input.clear();
			std::string tempString;
			input.open(getFileName().c_str());
			while (!input.eof()){
				std::getline(input, tempString);
				set1.insert(tempString);
			}
			input.close();
		}
		else if (select == 3){		//subtraction of file from current set.
			input.clear();
			std::string tempString;
			input.open(getFileName().c_str());
			std::set<std::string>::iterator it;
			while (!input.eof()){
				std::getline(input, tempString);
				it = set1.find(tempString);
				if (it != set1.end()){
					set1.erase(it);
				}


			}
			input.close();
		}
		else if (select == 4){		//Difference of file and current set.
			input.clear();
			std::string tempString;
			std::string sourceFileName = getFileName();

			input.open(sourceFileName.c_str());
			
			
			while (!input.eof()){
				std::getline(input, tempString);
				set1.insert(tempString);
			}
			input.close();
			output.open(sourceFileName.c_str());
			for (std::set<std::string>::iterator it = set1.begin(); it != set1.end(); ++it){
				tempString = *it + "\n";
				output << tempString;
			}
			output.close();
		}
		else if (select == 5){		//Intersection of file and set
			input.clear();
			std::string tempString;
			input.open(getFileName().c_str());

			while (!input.eof()){
				std::getline(input, tempString);
				if (set1.find(tempString) != set1.end()){
					set1.erase(set1.find(tempString));
				}
			}
			input.close();
		}
		else if (select == 6){		//reset set
			set1.clear();
		}
		else if (select == 7){		//output a set
			std::string outputFile ="./" + getFileName() + ".txt";
			output.open(outputFile);
			std::string tempString;
			for (std::set<std::string>::iterator it = set1.begin(); it != set1.end(); ++it){
				tempString = *it + "\n";
				output << tempString;
			}
			output.close();
		}
		
		else if (select == 8){		//print set
			for (std::set<std::string>::iterator it = set1.begin(); it != set1.end(); ++it)
				std::cout << *it << std::endl;
		}
		else if (select == 9){		

		}
		else if (select == 10){

		}
		else if (select == 11){

		}
		else if (select == 12){

		}
		else if (select == 13){

		}
		else if (select == 14){

		}
		else if (select == 15){

		}
	}
	return 0;
}