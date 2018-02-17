#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef PUCK_JS_H
#define PUCK_JS_H

class PuckJs
{
private:
	string _uuid;
	string _roomUuid;
	string _name;
	string _mac;

public:
	PuckJs();
	PuckJs(string, string, string, string);
	~PuckJs();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetName(string);
	string GetName();

	void SetMac(string);
	string GetMac();

	string JsonString();
	string ToString();
};

#endif
