//Leoncio Kian
//David Jimenez
//Davis Leighton
//G13

#include <iostream>
#include <vector>
using namespace std;
vector<int> tower0;
vector<int> tower1;
vector<int> tower2;
bool VERBOSE = true;
string silent = "-s";
void hanoi(int diskSize, vector<int> &source, vector <int> &dest, vector<int> &spare)
{

  if(diskSize == 0)
	{

	}
	else
	{

		hanoi(diskSize - 1, source, spare, dest);
	    dest.push_back(source.back());
	    source.pop_back();

		if(VERBOSE){
			std::cout << "=====================" << endl;
			std::cout << "Tower 0: " << endl;
			for (int i = 0; i < tower0.size(); i++){
				cout << tower0[i] << " ";
			}
			std::cout << endl;
			std::cout << "Tower 1: " << endl;
			for (int i = 0; i < tower2.size(); i++){
				cout << tower2[i] << " ";
			}
			std::cout << endl;
			std::cout << "Tower 2: " << endl;
			for (int i = 0; i < tower1.size(); i++){
				cout << tower1[i] << " ";
			}
			
			std::cout << endl;
		}
			hanoi(diskSize - 1, spare, dest, source);
		}
}

int main(int argc, char * argv[])
{
	if(argc == 2){
		if(argv[1] == silent){
			VERBOSE = false;
			
		}
	}
  int numOfDisks;
  cout << "Enter size: ";
  cin >> numOfDisks;
  cout << endl;
  for(int i = numOfDisks; i > 0; i--){
    tower0.push_back(i);
  }
  //Move all 3 disks from peg 0 to peg 1 using peg 2 as a temporary.
  if(VERBOSE){
	  std::cout << "=====================" << endl;
	  std::cout << "Tower 0: " << endl;
	  for (int i = 0; i < tower0.size(); i++){
		  cout << tower0[i] << " ";
	  }
	  std::cout << endl;
	  std::cout << "Tower 1: " << endl;
	  for (int i = 0; i < tower2.size(); i++){
		  cout << tower2[i] << " ";
	  }
	  std::cout << endl;
	  std::cout << "Tower 2: " << endl;
	  for (int i = 0; i < tower1.size(); i++){
		  cout << tower1[i] << " ";
	  }

	  std::cout << endl;
	}
  hanoi(numOfDisks, tower0, tower1, tower2);
  return 0;
}
