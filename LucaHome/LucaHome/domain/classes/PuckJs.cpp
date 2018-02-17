#include "PuckJs.h"

PuckJs::PuckJs()
{
	_uuid = "";
	_roomUuid = "";
	_name = "";
	_mac = "";
}

PuckJs::PuckJs(string uuid, string roomUuid, string name, string mac)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_name = name;
	_mac = mac;
}

PuckJs::~PuckJs()
{
}

void PuckJs::SetUuid(string uuid)
{
	_uuid = uuid;
}

string PuckJs::GetUuid()
{
	return _uuid;
}

void PuckJs::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string PuckJs::GetRoomUuid()
{
	return _roomUuid;
}

void PuckJs::SetName(string name)
{
	_name = name;
}

string PuckJs::GetName()
{
	return _name;
}

void PuckJs::SetMac(string mac)
{
	_mac = mac;
}

string PuckJs::GetMac()
{
	return _mac;
}

string PuckJs::JsonString()
{
	string str =
		string("{")
		+ string("\"PuckJs\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Mac\":\"") + _mac + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string PuckJs::ToString()
{
	string str = string("PuckJs { uuid: ") + _uuid
		+ string("; roomuuid: ") + _roomUuid
		+ string("; name: ") + _name
		+ string("; mac: ") + _mac
		+ string(" }");
	return str;
}
