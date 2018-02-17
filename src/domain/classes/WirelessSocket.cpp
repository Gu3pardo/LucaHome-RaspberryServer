#include "WirelessSocket.h"

WirelessSocket::WirelessSocket()
{
	_uuid = "";
	_roomUuid = "";
	_name = "";
	_code = "";
	_state = false;
}

WirelessSocket::WirelessSocket(string uuid, string roomUuid, string name, string code, bool state)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_name = name;
	_code = code;
	_state = state;
}

WirelessSocket::~WirelessSocket()
{
}

void WirelessSocket::SetUuid(string uuid)
{
	_uuid = uuid;
}

string WirelessSocket::GetUuid()
{
	return _uuid;
}

void WirelessSocket::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string WirelessSocket::GetRoomUuid()
{
	return _roomUuid;
}

void WirelessSocket::SetName(string name)
{
	_name = name;
}

string WirelessSocket::GetName()
{
	return _name;
}

void WirelessSocket::SetCode(string code)
{
	_code = code;
}

string WirelessSocket::GetCode()
{
	return _code;
}

void WirelessSocket::SetState(bool state) {
	_state = state;
}

bool WirelessSocket::GetState()
{
	return _state;
}

string WirelessSocket::JsonString()
{
	string str =
		string("{")
		+ string("\"WirelessSocket\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Code\":\"") + _code + string("\",")
		+ string("\"State\":") + Tools::ConvertBoolToStr(_state)
		+ string("}")
		+ string("}");
	return str;
}

string WirelessSocket::ToString()
{
	string str =
		string("WirelessSocket { uuid: ") + _uuid
		+ string("; roomuuid: ") + _roomUuid
		+ string("; name: ") + _name
		+ string("; code: ") + _code
		+ string("; state: ") + Tools::ConvertBoolToStr(_state)
		+ string(" }");
	return str;
}
