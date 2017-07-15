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
	PointDto _position;
	int _type;
	std::vector<std::string> _schedules;
	std::vector<std::string> _sockets;
	std::string _temperatureArea;
	int _visibility;

public:
	MapContentDto();
	MapContentDto(int, PointDto, int, std::vector<std::string>, std::vector<std::string>, std::string, int);
	~MapContentDto();

	int GetId();
	PointDto GetPosition();
	int GetType();
	std::vector<std::string> GetSchedules();
	std::vector<std::string> GetSockets();
	std::string GetTemperatureArea();
	int GetVisibility();

	std::string GetSchedulesString();
	std::string GetSocketsString();

	std::string GetRestString();
	std::string GetFileString();

	std::string ToString();
};

#endif
