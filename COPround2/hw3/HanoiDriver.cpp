/*
* HanoiDriver.cpp
*
*  Created on: Feb 17, 2014
*      Author: Joshua
*/

#include "HanoiDriver.h"
#include "Tower.h"
#include <stdexcept>
#include <sstream>

int moveCount = 0;

Tower *a;
Tower *b;
Tower *c;

// These two methods were copied from an online forum and are helpful to this, so I'm using them.
// Original link:  http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

// That thing on the end?  We call that a "function pointer."  Yes, it's real, and it's really a pointer.
// We are actually passing a FUNCTION as a parameter, via pointer!

// void (*callback)(void)
// void: return
//      (*callback) - function pointer, variable name "callback"
//                 (void) - argument list

void hanoi(int n, Tower* source, Tower* spare, Tower* destination, void(*callback)(void))
{
	if (n > 1)
		hanoi(n - 1, source, destination, spare, callback);

	destination->placeRing(source->takeRing());

	if (callback != 0) callback();

	if (n > 1)
		hanoi(n - 1, spare, source, destination, callback);
}

/**
* The true, core algorithm of the Towers of Hanoi.
* @param n - the number of pegs to be moved.
* @param source - the "source" tower
* @param spare - the "spare" / "middle" tower
* @param destination - the "destination" tower
*/
void hanoi(int n, Tower* source, Tower* spare, Tower* destination)
{
	hanoi(n - 1, source, destination, spare, 0);
}


char getDigitCharacter(int i)
{
	if (i < 0 || i > 36) throw out_of_range("value must be between 0 and 36");

	if (i < 10) return (char)(48 + i);
	else return (char)(55 + i);  // i=10 -> A, 65 = ASCII 'A'.
}

void outputMethod()
{
	//Cuts each Tower representation into individual lines.
	vector<string> aOutput = split(a->toString(), '\n');
	vector<string> bOutput = split(b->toString(), '\n');
	vector<string> cOutput = split(c->toString(), '\n');

	moveCount++;

	//string trueOutput = "";
	ostringstream ostr;

	/*
	* For the curious, note that the Tower.toString() method
	* uses return characters within it.  In order to place the
	* representation of all three towers beside each other,
	* I've already spliced their representations and am now
	* combining them appropriately to get our nice, "pretty" output.
	*/
	for (int i = 0; i < aOutput.size(); i++)
	{
		//trueOutput += aOutput[i] + " " + bOutput[i] + " " + cOutput[i] + "\n";
		ostr << aOutput[i] << " " << bOutput[i] << " " << cOutput[i] << endl;
	}

	//A little extra space is nice.
	cout << ostr.str();
	cout << endl;
	cout << "Moves so far: " << moveCount;
	cout << endl;
	cout << endl;
}

int main()
{
	a = new Tower(ringCount, ringCount);

	//Set up the first tower properly.  Largest rings must come first.
	for (int i = ringCount; i > 0; i--)
	{
		Ring r(i, getDigitCharacter(i));
		a->placeRing(r);
	}

	b = new Tower(ringCount, ringCount);
	c = new Tower(ringCount, ringCount);

	// TODO:  Note!  The signal method is called here, but we don't want it to contribute to the count.
	moveCount -= 1;  // Preemptive so the initial condition says "move count = 0".
	outputMethod();

	// See that last argument?  It's a FUNCTION pointer.
	hanoi(ringCount, a, b, c, outputMethod);

	delete a;
	delete b;
	delete c;

	return 0;
}

