#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef WIRELESS_SOCKET_H
#define WIRELESS_SOCKET_H

class WirelessSocket
{
protected:
	string _uuid;
	string _roomUuid;
	string _name;
	string _code;
	bool _state;

public:
	WirelessSocket();
	WirelessSocket(string, string, string, string, bool);
	~WirelessSocket();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetName(string);
	string GetName();

	void SetCode(string);
	string GetCode();

	void SetState(bool);
	bool GetState();

	string JsonString();
	string ToString();
};

#endif
