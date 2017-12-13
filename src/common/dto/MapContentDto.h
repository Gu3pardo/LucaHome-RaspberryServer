#include <string>
#include <cstring>
#include <iostream>

#include "PointDto.h"
#include "../utils/Tools.h"

#ifndef MAPCONTENT_DTO_H
#define MAPCONTENT_DTO_H

class MapContentDto {

private:
	int _id;
	std::string _type;
	int _typeId;
	PointDto _position;
	std::string _name;
	std::string _shortName;
	std::string _area;
	bool _visibility;

public:
	MapContentDto();
	MapContentDto(int, std::string, int, PointDto, std::string, std::string, std::string, bool);
	~MapContentDto();

	int GetId();
	std::string GetType();
	int GetTypeId();
	PointDto GetPosition();
	std::string GetName();
	std::string GetShortName();
	std::string GetArea();
	bool GetVisibility();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
