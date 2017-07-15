#include "MapContentDto.h"

MapContentDto::MapContentDto() {
	_id = -1;
	_position = PointDto();
	_type = -1;
	_temperatureArea = "";
	_visibility = -1;
}

MapContentDto::MapContentDto(
	int id,
	PointDto position,
	int type,
	std::vector<std::string> schedules,
	std::vector<std::string> sockets,
	std::string temperatureArea,
	int visibility)
{
	_id = id;
	_position = position;
	_type = type;
	_schedules = schedules;
	_sockets = sockets;
	_temperatureArea = temperatureArea;
	_visibility = visibility;
}

MapContentDto::~MapContentDto() {
}

int MapContentDto::GetId() {
	return _id;
}

PointDto MapContentDto::GetPosition() {
	return _position;
}

int MapContentDto::GetType() {
	return _type;
}

std::vector<std::string> MapContentDto::GetSchedules() {
	return _schedules;
}

std::vector<std::string> MapContentDto::GetSockets() {
	return _sockets;
}

std::string MapContentDto::GetTemperatureArea() {
	return _temperatureArea;
}

int MapContentDto::GetVisibility() {
	return _visibility;
}

std::string MapContentDto::GetSchedulesString() {
	std::stringstream out;
	for (int index = 0; index < _schedules.size(); index++) {
		out << _schedules[index] << "|";
	}
	return out.str();
}

std::string MapContentDto::GetSocketsString() {
	std::stringstream out;
	for (int index = 0; index < _sockets.size(); index++) {
		out << _sockets[index] << "|";
	}
	return out.str();
}

std::string MapContentDto::GetRestString() {
	std::string str = std::string("{mapcontent:")
		+ std::string("};{id:") + Tools::ConvertIntToStr(_id)
		+ std::string("};{position:") + _position.GetString()
		+ std::string("};{type:") + Tools::ConvertIntToStr(_type)
		+ std::string("};{schedules:") + GetSchedulesString()
		+ std::string("};{sockets:") + GetSocketsString()
		+ std::string("};{temperatureArea:") + _temperatureArea
		+ std::string("};{visibility:") + Tools::ConvertIntToStr(_visibility)
		+ std::string("};};");
	return str;
}

std::string MapContentDto::GetFileString() {
	std::string str = Tools::ConvertIntToStr(_id)
		+ std::string(":") + _position.GetString()
		+ std::string(":") + Tools::ConvertIntToStr(_type)
		+ std::string(":") + GetSchedulesString()
		+ std::string(":") + GetSocketsString()
		+ std::string(":") + _temperatureArea
		+ std::string(":") + Tools::ConvertIntToStr(_visibility)
		+ std::string(";");
	return str;
}

std::string MapContentDto::ToString() {
	std::string str = std::string("MapContentDto { ")
		+ std::string("; id:") + Tools::ConvertIntToStr(_id)
		+ std::string("; position: ") + _position.ToString()
		+ std::string("; type: ") + Tools::ConvertIntToStr(_type)
		+ std::string("; schedules: ") + GetSchedulesString()
		+ std::string("; Sockets: ") + GetSocketsString()
		+ std::string("; temperature: ") + _temperatureArea
		+ std::string("; visibility: ") + Tools::ConvertIntToStr(_visibility)
		+ std::string(" }");
	return str;
}

