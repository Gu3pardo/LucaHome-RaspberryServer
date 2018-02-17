#include <string>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef POSITION_H
#define POSITION_H

class Position {

private:
	int _x;
	int _y;

public:
	Position();
	Position(int, int);
	~Position();

	int GetX();
	int GetY();

	string JsonString();
	string ToString();
};

#endif
