#include "MediaServer.h"

MediaServer::MediaServer()
{
	_uuid = "";
	_roomUuid = "";
	_ip = "";
	_isSleepingServer = false;
	_wirelessSocketUuid = "";
}

MediaServer::MediaServer(string uuid, string roomUuid, string ip, bool isSleepingServer, string wirelessSocketUuid)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_ip = ip;
	_isSleepingServer = isSleepingServer;
	_wirelessSocketUuid = wirelessSocketUuid;
}

MediaServer::~MediaServer()
{
}

void MediaServer::SetUuid(string uuid)
{
	_uuid = uuid;
}

string MediaServer::GetUuid()
{
	return _uuid;
}

void MediaServer::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string MediaServer::GetRoomUuid()
{
	return _roomUuid;
}

void MediaServer::SetIp(string ip)
{
	_ip = ip;
}

string MediaServer::GetIp()
{
	return _ip;
}

void MediaServer::SetIsSleepingServer(bool isSleepingServer)
{
	_isSleepingServer = isSleepingServer;
}

bool MediaServer::IsSleepingServer()
{
	return _isSleepingServer;
}

void MediaServer::SetWirelessSocektUuid(string wirelessSocketUuid)
{
	_wirelessSocketUuid = wirelessSocketUuid;
}

string MediaServer::GetWirelessSocketUuid()
{
	return _wirelessSocketUuid;
}

string MediaServer::JsonString()
{
	string str =
		string("{")
		+ string("\"MediaServer\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"Ip\":\"") + _ip + string("\",")
		+ string("\"IsSleepingServer\":") + Tools::ConvertBoolToStr(_isSleepingServer) + string(",")
		+ string("\"WirelessSocketUuid\":") + _wirelessSocketUuid + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string MediaServer::ToString()
{
	string str =
		string("MediaServer { uuid: ") + _uuid
		+ string("; roomUuid: ") + _roomUuid
		+ string("; ip: ") + _ip
		+ string("; isSleepingServer: ") + Tools::ConvertBoolToStr(_isSleepingServer)
		+ string("; wirelessSocketUuid: ") + _wirelessSocketUuid
		+ string(" }");
	return str;
}
