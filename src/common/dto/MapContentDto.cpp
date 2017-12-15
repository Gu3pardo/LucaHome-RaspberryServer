#include "MapContentDto.h"

MapContentDto::MapContentDto() {
	_id = -1;
	_type = "";
	_typeId = -1;
	_position = PointDto();
	_name = "";
	_shortName = "";
	_area = "";
	_visibility = true;
}

MapContentDto::MapContentDto(
	int id,
	std::string type,
	int typeId,
	PointDto position,
	std::string name,
	std::string shortName,
	std::string area,
	bool visibility)
{
	_id = id;
	_type = type;
	_typeId = typeId;
	_position = position;
	_name = name;
	_shortName = shortName;
	_area = area;
	_visibility = visibility;
}

MapContentDto::~MapContentDto() {
}

int MapContentDto::GetId() {
	return _id;
}

std::string MapContentDto::GetType() {
	return _type;
}

int MapContentDto::GetTypeId() {
	return _typeId;
}

PointDto MapContentDto::GetPosition() {
	return _position;
}

std::string MapContentDto::GetName() {
	return _name;
}

std::string MapContentDto::GetShortName() {
	return _shortName;
}

std::string MapContentDto::GetArea() {
	return _area;
}

bool MapContentDto::GetVisibility() {
	return _visibility;
}

std::string MapContentDto::SaveString() {
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _type + ":"
		+ Tools::ConvertIntToStr(_typeId) + ":"
		+ _position.SaveString() + ":"
		+ _name + ":"
		+ _shortName + ":"
		+ _area + ":"
		+ Tools::ConvertBoolToStr(_visibility) + ";";
	return str;
}

std::string MapContentDto::JsonString() {
	std::string str =
		std::string("{")
		+ std::string("\"MapContent\":")
		+ std::string("{")
		+ std::string("\"ID\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Type\":\"") + _type + std::string("\",")
		+ std::string("\"TypeId\":") + Tools::ConvertIntToStr(_typeId) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"ShortName\":\"") + _shortName + std::string("\",")
		+ std::string("\"Area\":\"") + _area + std::string("\",")
		+ std::string("\"Visibility\":") + Tools::ConvertBoolToStr(_visibility) + std::string(",")
		+ std::string("\"Position\":")
		+ _position.JsonString() + ":"
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string MapContentDto::PhpString() {
	std::stringstream out;

	out << "mapcontent::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _type << "::"
		<< Tools::ConvertIntToStr(_typeId) << "::"
		<< _position.SaveString() << "::"
		<< _name << "::"
		<< _shortName << "::"
		<< _area << "::"
		<< Tools::ConvertBoolToStr(_visibility) << ";";

	return out.str();
}

std::string MapContentDto::ToString() {
	std::string str = std::string("MapContentDto { ")
		+ std::string("; id:") + Tools::ConvertIntToStr(_id)
		+ std::string("; type: ") + _type
		+ std::string("; typeId:") + Tools::ConvertIntToStr(_typeId)
		+ std::string("; position: ") + _position.ToString()
		+ std::string("; name: ") + _name
		+ std::string("; shortName: ") + _shortName
		+ std::string("; area: ") + _area
		+ std::string("; visibility: ") + Tools::ConvertBoolToStr(_visibility)
		+ std::string(" }");
	return str;
}

