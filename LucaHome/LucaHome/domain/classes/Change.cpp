#include "Change.h"

Change::Change()
{
	Change("", "", "", time(0));
}

Change::Change(string uuid, string type, string userName, time_t changeTime)
{
	_uuid = uuid;
	_type = type;
	_userName = userName;
	_time = changeTime;
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

void Change::SetTime(time_t newtime)
{
	_time = newtime;
}

time_t Change::GetTime()
{
	return _time;
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
		+ string("\"Time\":") + Tools::ConvertIntToStr(_time)
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
		+ string("; time: ") + Tools::ConvertIntToStr(_time)
		+ string(" }");
	return str;
}
