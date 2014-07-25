//You will need these 2 includes for randomness to work
#include <cstdlib>
#include <ctime>
#include <iostream>


// You will need to place these functions above main or the
// compiler won't know what they are

// This function returns a random number between 1 and 100

int get_random()
{
  int low = 1;
  int high = 100;
  return low + (rand()%(high-low));
}

// Required to ensure proper randomness. Call this once and only once from the first line in main:
// int main()
// {
//   set_up_random();
//   // Your other code
// }

void set_up_random()
{
  srand(time(0));
}

int main(){
	int answer;
	int guess = 101;
	char cont;
	set_up_random();
	answer = get_random();
	
	std::cout << "Welcome to the Guessing Game! The goal of the game is to guess the number between 1 and 100!" << std::endl; 
	while(answer != guess){
		std::cout <<"Please enter your guess -- ";
	
		std::cin >> guess;
		if(guess > answer){
			std::cout << "Too high! Try again." << std::endl;
		}
		else if(guess < answer){
			std::cout << "Too low! Try again." << std::endl;
		}
		else if(guess == answer){
			std::cout << "Correct!  Play again? (Y/n) -- ";
			std::cin >> cont;
			if(cont == 'Y' || cont == 'y'){
				answer = get_random();
				guess = 101;
				std::cout << "Welcome to the Guessing Game! The goal of the game is to guess the number between 1 and 100!" << std::endl; 
			}
			else if(cont == 'N' || cont == 'n'){
				std::cout << "Goodbye!" << std::endl;
			}
		}
	}
	return 0;
}
