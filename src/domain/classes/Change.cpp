#include "Change.h"

Change::Change()
{
	_uuid = "";
	_type = "";
	_userName = "";
	_hour = 0;
	_minute = 0;
	_day = 1;
	_month = 1;
	_year = 1970;
}

Change::Change(string uuid, string type, string userName, int hour, int minute, int day, int month, int year)
{
	_uuid = uuid;
	_type = type;
	_userName = userName;
	_hour = hour;
	_minute = minute;
	_day = day;
	_month = month;
	_year = year;
}

Change::~Change()
{
}

void Change::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Change::GetUuid()
{
	return _uuid;
}

void Change::SetType(string type)
{
	_type = type;
}

string Change::GetType()
{
	return _type;
}

void Change::SetUserName(string userName)
{
	_userName = userName;
}

string Change::GetUserName()
{
	return _userName;
}

void Change::SetHour(int hour)
{
	_hour = hour;
}

int Change::GetHour()
{
	return _hour;
}

void Change::SetMinute(int minute)
{
	_minute = minute;
}

int Change::GetMinute()
{
	return _minute;
}

void Change::SetDay(int day)
{
	_day = day;
}

int Change::GetDay()
{
	return _day;
}

void Change::SetMonth(int month)
{
	_month = month;
}

int Change::GetMonth()
{
	return _month;
}

void Change::SetYear(int year)
{
	_year = year;
}

int Change::GetYear()
{
	return _year;
}

string Change::JsonString()
{
	string str =
		string("{")
		+ string("\"Change\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"UserName\":\"") + _userName + string("\",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}") + string(",")
		+ string("\"Time\":")
		+ string("{")
		+ string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + string(",")
		+ string("\"Minute\":") + Tools::ConvertIntToStr(_minute)
		+ string("}")
		+ string("}")
		+ string("}");
	return str;
}

string Change::ToString()
{
	string str =
		string("Change { uuid: ") + _uuid
		+ string("; type: ") + _type
		+ string("; userName: ") + _userName
		+ string("; hour: ") + Tools::ConvertIntToStr(_hour)
		+ string("; minute: ") + Tools::ConvertIntToStr(_minute)
		+ string("; day: ") + Tools::ConvertIntToStr(_day)
		+ string("; month: ") + Tools::ConvertIntToStr(_month)
		+ string("; year: ") + Tools::ConvertIntToStr(_year)
		+ string(" }");
	return str;
}
