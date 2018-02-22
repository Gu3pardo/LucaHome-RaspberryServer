#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef CHANGE_H
#define CHANGE_H

class Change
{
private:
	string _uuid;
	string _type;
	string _userName;
	time_t _time;

public:
	Change();
	Change(string, string, string, time_t);
	~Change();

	void SetUuid(string);
	string GetUuid();

	void SetType(string);
	string GetType();

	void SetUserName(string);
	string GetUserName();

	void SetTime(time_t);
	time_t GetTime();

	string JsonString();
	string ToString();
};

#endif
