#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef METER_LOG_ITEM_H
#define METER_LOG_ITEM_H

class MeterLogItem
{
private:
	string _uuid;
	string _roomUuid;
	string _typeUuid;
	string _type;
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;
	string _meterId;
	double _value;
	string _imageName;

public:
	MeterLogItem();
	MeterLogItem(string, string, string, string, int, int, int, int, int, string, double, string);
	~MeterLogItem();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetTypeUuid(string);
	string GetTypeUuid();

	void SetType(string);
	string GetType();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetMeterId(string);
	string GetMeterId();

	void SetValue(double);
	double GetValue();

	void SetImageName(string);
	string GetImageName();

	string JsonString();
	string ToString();
};

#endif
