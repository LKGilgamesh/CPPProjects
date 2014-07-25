#include<fstream>
#include<string>
#include<iostream>

int readInput(std::ifstream &in){
	if(!in.fail() || in.good()){
		while(!in.eof()){
			std::string tempString;
			std::getline(in, tempString);
			std::cout << tempString << std::endl;
		}
		return 1;
	}
	else{
		return 0;
	}
	
}
int echo_1(std::string str){
	std::ifstream input;
	input.open(str.c_str());
	return readInput(input);
}
int echo_2(std::ifstream &in){
	return readInput(in);
}
void echo_3(std::string str,int & result){
	std::ifstream input;
	input.open(str.c_str());
	result = readInput(input);
}
void echo_4(std::ifstream &in,int &result){
	result = readInput(in);
}
void echo_5(std::ifstream &in,int &result){
	
	if(!in.fail()){
		std::ofstream output;
		output.open("./output.txt");
		if(output.is_open()){
			while(!in.eof()){
				std::string tempString;
				std::getline(in, tempString);
				tempString += "\n";
				output.write(tempString.c_str(),tempString.size());
			}
		result = 1;
		output.close();
		}
		else{
			result = -1;
		}
	}
	else{
		result = 0;
	}
}
int main(){
	std::ifstream input;
	int result [5];
	std::cout << "echo_1" << std::endl;
	result[0] = echo_1("input.txt");


	input.open("input.txt");
	std::cout << "echo_2" << std::endl;
	result[1] = echo_2(input);
	input.close();


	std::cout << "echo_3" << std::endl;
	echo_3("input.txt",result[2]);


	input.open("input.txt");
	std::cout << "echo_4" << std::endl;
	echo_4(input,result[3]);
	input.close();

	input.open("input.txt");
	std::cout << "echo_5" << std::endl;
	echo_5(input,result[4]);
	input.close();

	for(int i = 0; i < 5;i++){
		std::cout << "result" << i+1 << " = " << result[i] << std::endl;
	}

	std::cout << "echo_1" << std::endl;
	result[0] = echo_1("input21.txt");
	std::cout << "result1 = " << result[0] << std::endl;

	std::cout << "echo_3" << std::endl;
	echo_3("input32.txt",result[2]);
	std::cout << "result1 = " << result[0] << std::endl;

	std::cout << "echo_1" << std::endl;
	result[0] = echo_1("input2.txt");


	input.open("input2.txt");
	std::cout << "echo_2" << std::endl;
	result[1] = echo_2(input);
	input.close();


	std::cout << "echo_3" << std::endl;
	echo_3("input2.txt",result[2]);


	input.open("input2.txt");
	std::cout << "echo_4" << std::endl;
	echo_4(input,result[3]);
	input.close();

	for(int i = 0; i < 4;i++){
		std::cout << "result" << i+1 << " = " << result[i] << std::endl;
	}
	return 0;
}
