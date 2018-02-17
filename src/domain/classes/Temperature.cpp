#include "Temperature.h"

Temperature::Temperature()
{
	_uuid = "";
	_roomUuid = "";
	_temperature = 0.0;
	_day = 1;
	_month = 1;
	_year = 1970;
	_hour = 0;
	_minute = 0;
	_temperatureType = 0;
	_sensorPath = "";
	_graphPath = "";
}

Temperature::Temperature(
	string uuid, string roomUuid, double temperature,
	int day, int month, int year,
	int hour, int minute,
	int temperatureType, string sensorPath, string graphPath)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_temperature = temperature;
	_day = day;
	_month = month;
	_year = year;
	_hour = hour;
	_minute = minute;
	_temperatureType = temperatureType;
	_sensorPath = sensorPath;
	_graphPath = graphPath;
}

Temperature::~Temperature()
{
}

void Temperature::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Temperature::GetUuid()
{
	return _uuid;
}

void Temperature::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string Temperature::GetRoomUuid()
{
	return _roomUuid;
}

void Temperature::SetTemperature(double temperature)
{
	_temperature = temperature;
}

double Temperature::GetTemperature()
{
	return _temperature;
}

void Temperature::SetDay(int day)
{
	_day = day;
}

int Temperature::GetDay()
{
	return _day;
}

void Temperature::SetMonth(int month)
{
	_month = month;
}

int Temperature::GetMonth()
{
	return _month;
}

void Temperature::SetYear(int year)
{
	_year = year;
}

int Temperature::GetYear()
{
	return _year;
}

void Temperature::SetHour(int hour)
{
	_hour = hour;
}

int Temperature::GetHour()
{
	return _hour;
}

void Temperature::SetMinute(int minute)
{
	_minute = minute;
}

int Temperature::GetMinute()
{
	return _minute;
}

void Temperature::SetTemperatureType(int temperatureType)
{
	_temperatureType = temperatureType;
}

int Temperature::GetTemperatureType()
{
	return _temperatureType;
}

void Temperature::SetSensorPath(string sensorPath)
{
	_sensorPath = sensorPath;
}

string Temperature::GetSensorPath()
{
	return _sensorPath;
}

void Temperature::SetGraphPath(string graphPath)
{
	_graphPath = graphPath;
}

string Temperature::GetGraphPath()
{
	return _graphPath;
}

string Temperature::JsonString()
{
	string str =
		string("{")
		+ string("\"Temperature\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"Value\":") + Tools::ConvertDoubleToStr(_temperature) + string(",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}")
		+ string(",")
		+ string("\"Time\":")
		+ string("{")
		+ string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + string(",")
		+ string("\"Minute\":") + Tools::ConvertIntToStr(_minute)
		+ string("}")
		+ string(",")
		+ string("\"TemperatureType\":") + Tools::ConvertIntToStr(_temperatureType) + string(",")
		+ string("\"SensorPath\":\"") + _sensorPath + string("\",")
		+ string("\"GraphPath\":\"") + _graphPath + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string Temperature::ToString()
{
	string str = string("Temperature { uuid: ") + _uuid
		+ string("; roomuuid: ") + _roomUuid
		+ string("; value: ") + Tools::ConvertDoubleToStr(_temperature)
		+ string(" }");
	return str;
}
