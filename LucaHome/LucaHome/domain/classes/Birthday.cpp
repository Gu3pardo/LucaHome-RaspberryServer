#include "Birthday.h"

Birthday::Birthday()
{
	_uuid = "";
	_name = "";
	_day = 1;
	_month = 1;
	_year = 1900;
	_group = "";
	_remindMe = false;
	_sentMail = false;
}

Birthday::Birthday(string uuid, string name, int day, int month, int year, string group, bool remindMe, bool sentMail)
{
	_uuid = uuid;
	_name = name;
	_day = day;
	_month = month;
	_year = year;
	_group = group;
	_remindMe = remindMe;
	_sentMail = sentMail;
}

Birthday::~Birthday()
{
}

void Birthday::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Birthday::GetUuid()
{
	return _uuid;
}

void Birthday::SetName(string name)
{
	_name = name;
}

string Birthday::GetName()
{
	return _name;
}

void Birthday::SetDay(int day)
{
	_day = day;
}

int Birthday::GetDay()
{
	return _day;
}

void Birthday::SetMonth(int month)
{
	_month = month;
}

int Birthday::GetMonth()
{
	return _month;
}

void Birthday::SetYear(int year)
{
	_year = year;
}

int Birthday::GetYear()
{
	return _year;
}

int Birthday::GetAge()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayYear = now->tm_year + 1900;
	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (_month < todayMonth)
	{
		return todayYear - _year;
	}
	else if (_month == todayMonth)
	{
		if (_day > todayDay)
		{
			return todayYear - _year - 1;
		}
		else
		{
			return todayYear - _year;
		}
	}
	else
	{
		return todayYear - _year - 1;
	}
}

bool Birthday::HasBirthday()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (todayMonth == _month && todayDay == _day)
	{
		return true;
	}

	return false;
}

void Birthday::SetGroup(string group)
{
	_group = group;
}

string Birthday::GetGroup()
{
	return _group;
}

void Birthday::SetSentMail(bool sentMail) {
	_sentMail = sentMail;
}

bool Birthday::GetSentMail() {
	return _sentMail;
}

void Birthday::SetRemindMe(bool remindMe) {
	_remindMe = remindMe;
}

bool Birthday::GetRemindMe() {
	return _remindMe;
}

string Birthday::JsonString()
{
	string str =
		string("{")
		+ string("\"Birthday\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"RemindMe\":") + Tools::ConvertBoolToStr(_remindMe) + string(",")
		+ string("\"SentMail\":") + Tools::ConvertBoolToStr(_sentMail) + string(",")
		+ string("\"Group\":\"") + _group + string("\",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}")
		+ string("}")
		+ string("}");
	return str;
}

string Birthday::ToString()
{
	string str = string("Birthday { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; day: ") + Tools::ConvertIntToStr(_day)
		+ string("; month: ") + Tools::ConvertIntToStr(_month)
		+ string("; year: ") + Tools::ConvertIntToStr(_year)
		+ string("; group: ") + _group
		+ string("; remindme: ") + Tools::ConvertBoolToStr(_remindMe)
		+ string("; sentmail: ") + Tools::ConvertBoolToStr(_sentMail)
		+ string(" }");
	return str;
}
