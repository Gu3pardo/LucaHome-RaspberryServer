#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef PUCKJS_DTO_H
#define PUCKJS_DTO_H

class PuckJsDto
{
private:
	int _id;
	std::string _name;
	std::string _area;
	std::string _mac;

public:
	PuckJsDto();
	PuckJsDto(int, std::string, std::string, std::string);
	~PuckJsDto();

	void SetId(int);
	int GetId();

	void SetName(std::string);
	std::string GetName();

	void SetArea(std::string);
	std::string GetArea();

	void SetMac(std::string);
	std::string GetMac();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
