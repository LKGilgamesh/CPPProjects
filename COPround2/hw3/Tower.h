/*
* Tower.h
*
*  Created on: Feb 17, 2014
*      Author: Joshua
*/

#ifndef TOWER_H_
#define TOWER_H_

using namespace std;

#include <iostream>
#include <vector>
#include "Ring.h"

// The default copy constructor and assignment
// methods will suffice here, assuming that
// vector's are written appropriately by C++'s
// devs.

class Tower
{
public:
	Tower(int maxHeight, int maxWidth);
	~Tower();

	Ring takeRing();
	void placeRing(const Ring& r);

	string toString();

private:
	vector<Ring> rings;
	int maxHeight;
	int maxWidth;
};

#endif /* TOWER_H_ */
