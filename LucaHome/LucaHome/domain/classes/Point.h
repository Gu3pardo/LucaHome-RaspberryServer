#include <string>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef POINT_H
#define POINT_H

class Point {

private:
	int _x;
	int _y;

public:
	Point();
	Point(int, int);
	~Point();

	int GetX();
	int GetY();

	string JsonString();
	string ToString();
};

#endif
