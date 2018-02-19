#include <string>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef POLYLINE_H
#define POLYLINE_H

class Polyline {

private:
	int _x;
	int _y;

public:
	Polyline();
	Polyline(int, int);
	~Polyline();

	int GetX();
	int GetY();

	string JsonString();
	string ToString();
};

#endif
