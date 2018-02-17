#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef MEDIASERVER_H
#define MEDIASERVER_H

class MediaServer
{
private:
	string _uuid;
	string _roomUuid;
	string _ip;
	bool _isSleepingServer;
	string _wirelessSocketUuid;

public:
	MediaServer();
	MediaServer(string, string, string, bool, string);
	~MediaServer();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetIp(string);
	string GetIp();

	void SetIsSleepingServer(bool);
	bool IsSleepingServer();

	void SetWirelessSocektUuid(string);
	string GetWirelessSocketUuid();

	string JsonString();
	string ToString();
};

#endif
