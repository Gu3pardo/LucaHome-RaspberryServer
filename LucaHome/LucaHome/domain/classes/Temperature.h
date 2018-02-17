#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

class Temperature
{
private:
	string _uuid;
	string _roomUuid;
	double _temperature;
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;
	int _temperatureType;
	string _sensorPath;
	string _graphPath;

public:
	Temperature();
	Temperature(string, string, double, int, int, int, int, int, int, string, string);
	~Temperature();

	void SetUuid(string);
	string GetUuid();

	void SetRoomUuid(string);
	string GetRoomUuid();

	void SetTemperature(double);
	double GetTemperature();

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

	void SetTemperatureType(int);
	int GetTemperatureType();

	void SetSensorPath(string);
	string GetSensorPath();

	void SetGraphPath(string);
	string GetGraphPath();

	string JsonString();
	string ToString();
};

#endif
