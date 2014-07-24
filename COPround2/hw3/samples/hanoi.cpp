#include <iostream>
#include <vector>
using namespace std;
vector<int> tower0;
vector<int> tower1;
vector<int> tower2;
/*
  Hanoi is the capital of Vietnam. It is also a logical puzzle game that can be solved very effectively 
  with recursion. The setup of Hanoi is simple. We have three pegs. On each of these pegs is a series 
  of disks decreasing in size from the bottom of the peg to the top of the peg. The goal is to move  
  all these disks to another peg following these rules: 
    -Only one disk can be moved at a time. 
    -Only the topmost disk of any given peg can be moved to another peg. 
    -A larger disk cannot be placed ontop a smaller disk. 
   
  The simplest way of doing this is via Divide and Conquer.  
  The code is simple, but keeping track of what is going on may cause your brain to have a stack-overflow.
  
  Params:
    diskSize refers to the maximum number of disks we wish to move. If we have 5 disks and we wish
    to move all five disks to another peg then this value should be 5. 
    5 = largest disk and 0 = smallest disk.
  
    source is the peg where the disks currently exist.
  
    dest is the peg we want the disks to be moved to.
  
    spare is the peg that temporally stores pegs. This is necessary in order for us to shuffle disks
    around without violating the rules.
*/
void hanoi(int diskSize, vector<int> source, vector <int> dest, vector<int> spare)
{
  //This is our standard termination case. We get to here when we are operating on the 
  //smallest possible disk.
  if(diskSize == 0)
	{
		std::cout << "=====================" << endl;
    std::cout << "Tower 0: " << endl;
    for(int i = 0; i < tower0.size();i++){
      cout << tower0[i] << " ";
    }
    std::cout << endl;
    std::cout << "Tower 1: " << endl;
    for(int i = 0; i < tower1.size();i++){
      cout << tower1[i] << " ";
    }
    std::cout << endl;
    std::cout << "Tower 2: " << endl;
  for(int i = 0; i < tower2.size();i++){
      cout << tower2[i] << " ";
    }
    std::cout << endl;

    std::cout << "=====================" << endl;
	}
	else
	{
		//Move all disks smaller than this one over to the spare.
    //So if diskSize is 5, we move 4 disks to the spare. This leaves us with 1 disk
    //on the source peg.
    //Note the placement of the params.
    //We are now using the dest peg as the spare peg. This causes each recursion to ping-pong
    //the spare and dest pegs.
    dest.push_back(source.back());
    source.pop_back();

		hanoi(diskSize - 1, source, spare, dest);

		//Move the remaining disk to the destination peg.
		std::cout << "=====================" << endl;
    std::cout << "Tower 0: " << endl;
    for(int i = 0; i < tower0.size();i++){
      cout << tower0[i] << " ";
    }
    std::cout << endl;
    std::cout << "Tower 1: " << endl;
    for(int i = 0; i < tower1.size();i++){
      cout << tower1[i] << " ";
    }
    std::cout << endl;
    std::cout << "Tower 2: " << endl;
  for(int i = 0; i < tower2.size();i++){
      cout << tower2[i] << " ";
    }
    std::cout << endl;

    std::cout << "=====================" << endl;
		//Move the disks we just moved to the spare back over to the dest peg.
		hanoi(diskSize - 1, spare, dest, source);
	}
}

int main()
{
  int numOfDisks;
  cin >> numOfDisks;
  for(int i = numOfDisks; i > 0; i--){
    tower0.push_back(i);
  }
  //Move all 3 disks from peg 0 to peg 1 using peg 2 as a temporary.
  hanoi(numOfDisks, tower0, tower1, tower2);
  return 0;
}