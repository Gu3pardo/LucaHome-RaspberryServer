#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef WIRELESS_SCHEDULE_H
#define WIRELESS_SCHEDULE_H

class WirelessSchedule
{
protected:

	string _uuid;
	string _name;
	int _weekday;
	int _hour;
	int _minute;
	bool _isActive;
	string _gpioUuid;
	bool _gpioAction;
	string _wirelessSocketUuid;
	bool _wirelessSocketAction;
	string _wirelessSwitchUuid;

public:
	WirelessSchedule();
	WirelessSchedule(string, string, int, int, int, bool, string, bool, string, bool, string);
	~WirelessSchedule();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetWeekday(int);
	int GetWeekday();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetActive(bool);
	bool IsActive();

	void SetGpioUuid(string);
	string GetGpioUuid();

	void SetGpioAction(bool);
	bool GetGpioAction();

	void SetWirelessSocketUuid(string);
	string GetWirelessSocketUuid();

	void SetWirelessSocketAction(bool);
	bool GetWirelessSocketAction();

	void SetWirelessSwitchUuid(string);
	string GetWirelessSwitchUuid();

	string JsonString();
	string ToString();
};

#endif