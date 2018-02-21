#include "MapContent.h"

MapContent::MapContent() {
	MapContent("", "", "", Point(), "", "", true);
}

MapContent::MapContent(
	string uuid,
	string typeUuid,
	string type,
	Point position,
	string name,
	string shortName,
	bool visibility)
{
	_uuid = uuid;
	_typeUuid = typeUuid;
	_type = type;
	_position = position;
	_name = name;
	_shortName = shortName;
	_visibility = visibility;
}

MapContent::~MapContent() {
}

string MapContent::GetUuid() {
	return _uuid;
}

string MapContent::GetTypeUuid() {
	return _typeUuid;
}

string MapContent::GetType() {
	return _type;
}

Point MapContent::GetPosition() {
	return _position;
}

string MapContent::GetName() {
	return _name;
}

string MapContent::GetShortName() {
	return _shortName;
}

bool MapContent::GetVisibility() {
	return _visibility;
}

string MapContent::JsonString() {
	string str =
		string("{")
		+ string("\"MapContent\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"TypeUuid\":\"") + _typeUuid + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"ShortName\":\"") + _shortName + string("\",")
		+ string("\"Visibility\":") + Tools::ConvertBoolToStr(_visibility) + string(",")
		+ string("\"Position\":")
		+ _position.JsonString()
		+ string("}")
		+ string("}");
	return str;
}

std::string MapContent::ToString() {
	std::string str = std::string("MapContent { ")
		+ std::string("; uuid:") + _uuid
		+ std::string("; typeuuid:") + _typeUuid
		+ std::string("; type: ") + _type
		+ std::string("; name: ") + _name
		+ std::string("; shortName: ") + _shortName
		+ std::string("; visibility: ") + Tools::ConvertBoolToStr(_visibility)
		+ std::string("; position: ") + _position.ToString()
		+ std::string(" }");
	return str;
}

