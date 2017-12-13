#include <string>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef POINT_DTO_H
#define POINT_DTO_H

class PointDto {

private:
	int _x;
	int _y;

public:
	PointDto();
	PointDto(int, int);
	~PointDto();

	int GetX();
	int GetY();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
