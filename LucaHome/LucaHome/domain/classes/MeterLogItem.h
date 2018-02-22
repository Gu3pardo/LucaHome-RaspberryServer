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
	string _meterId;
	double _value;
	string _imageName;
	time_t _saveDateTime;

public:
	MeterLogItem();
	MeterLogItem(string, string, string, string, string, double, string, time_t);
	~MeterLogItem();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetTypeUuid(string);
	string GetTypeUuid();

	void SetType(string);
	string GetType();

	void SetMeterId(string);
	string GetMeterId();

	void SetValue(double);
	double GetValue();

	void SetImageName(string);
	string GetImageName();

	void SetSaveDateTime(time_t);
	time_t GetSaveDateTime();

	string JsonString();
	string ToString();
};

#endif
