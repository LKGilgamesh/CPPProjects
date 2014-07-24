/*
* Ring.cpp
*
*  Created on: Feb 17, 2014
*      Author: Joshua
*/

#include "Ring.h"
#include <sstream>

Ring::Ring(int width, char rep)
{
	this->width = width;
	this->representation = rep;
}

int Ring::getWidth()
{
	return width;
}

string Ring::getString()
{
	ostringstream ostr;

	for (int i = 0; i < 2 * width - 1; i++)
		ostr << representation;

	return ostr.str();
}

bool Ring::operator<(const Ring& r)
{
	return width < r.width;
}

