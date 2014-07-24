/*
* Ring.h
*
*  Created on: Feb 17, 2014
*      Author: Joshua
*/

#ifndef RING_H_
#define RING_H_

#include <string>

using namespace std;

// NOTE:  For this class, the default shallow-copy
// and shallow-assignment operators are fine.

class Ring
{
public:
	Ring(int width, char rep);
	int getWidth();
	string getString();

	bool operator<(const Ring& r);

private:
	int width;
	char representation;
};

#endif /* RING_H_ */
