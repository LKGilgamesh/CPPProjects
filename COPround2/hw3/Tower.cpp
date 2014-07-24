/*
* Tower.cpp
*
*  Created on: Feb 17, 2014
*      Author: Joshua
*/

#include "Tower.h"
#include <stdexcept>
#include <sstream>

using namespace std;

Tower::Tower(int maxHeight, int maxWidth)
{
	this->maxHeight = maxHeight;
	this->maxWidth = maxWidth;
}

Tower::~Tower()
{
}

Ring Tower::takeRing()
{
	Ring r = rings.back();
	rings.pop_back();

	return r;
}

void Tower::placeRing(const Ring& r)
{
	if (rings.size() > 0)
	{
		if (rings.back() < r)
		{
			throw invalid_argument("Ring is too large to place!");
		}
	}
	rings.push_back(r);
}

string Tower::toString()
{
	ostringstream ostr;

	int ringCount = rings.size();
	int pegHeight = maxHeight + 1 - ringCount;

	for (int i = 0; i < pegHeight; i++)
	{
		ostr << string(maxWidth, ' ') << '|' << string(maxWidth, ' ') << endl;
	}

	// Remember:  the end/back of our vector is the "top" of the peg/stack!
	for (int r = ringCount - 1; r >= 0; r--)
	{
		string spacing(maxWidth + 1 - rings[r].getWidth(), ' ');

		ostr << spacing << rings[r].getString() << spacing << endl;
	}

	ostr << string(2 * maxWidth + 1, '=');

	return ostr.str();
}
