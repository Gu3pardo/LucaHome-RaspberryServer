#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef WIRELESS_TASK_H
#define WIRELESS_TASK_H

class WirelessTask
{
private:
	string _parentUuid;
	int _parentType;
	time_t _time;
	int _weekday;
	int _done;
	int _active;

public:
	WirelessTask();
	WirelessTask(string, int, time_t, int);
	~WirelessTask();

	void SetParentUuid(string);
	string GetParentUuid();

	void SetParentType(int);
	int GetParentType();

	void SetTime(time_t);
	time_t GetTime();

	void SetWeekday(int);
	int GetWeekday();

	void SetDone(int);
	int IsDone();

	string ToString();
};

#endif
