#include "Room.h"

Room::Room()
{
	_uuid = "";
	_name = "";
	_type = 0;
}

Room::Room(string uuid, string name, int type)
{
	_uuid = uuid;
	_name = name;
	_type = type;
}

Room::~Room()
{
}

void Room::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Room::GetUuid()
{
	return _uuid;
}

void Room::SetName(string name)
{
	_name = name;
}

string Room::GetName()
{
	return _name;
}

void Room::SetType(int type)
{
	_type = type;
}

int Room::GetType()
{
	return _type;
}

string Room::JsonString()
{
	string str =
		string("{")
		+ string("\"Room\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Type\":") + Tools::ConvertIntToStr(_type) + string("")
		+ string("}")
		+ string("}");
	return str;
}

string Room::ToString()
{
	string str = string("Room { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; type: ") + Tools::ConvertIntToStr(_type)
		+ string(" }");
	return str;
}
