#include "WirelessTask.h"

WirelessTask::WirelessTask()
{
	_done = 0;
}

WirelessTask::WirelessTask(string parentUuid, int parentType, time_t time, int weekday)
{
	_parentUuid = parentUuid;
	_parentType = parentType;
	memcpy(&_time, &time, sizeof(time_t));
	_weekday = weekday;
	_done = 0;
}

WirelessTask::~WirelessTask()
{
}

void WirelessTask::SetParentUuid(string parentUuid)
{
	_parentUuid = parentUuid;
}

string WirelessTask::GetParentUuid()
{
	return _parentUuid;
}

void WirelessTask::SetParentType(int parentType)
{
	_parentType = parentType;
}

int WirelessTask::GetParentType()
{
	return _parentType;
}

void WirelessTask::SetTime(time_t time)
{
	_time = time;
}

time_t WirelessTask::GetTime()
{
	return _time;
}

void WirelessTask::SetWeekday(int weekday)
{
	_weekday = weekday;
}

int WirelessTask::GetWeekday()
{
	return _weekday;
}

void WirelessTask::SetDone(int done)
{
	_done = done;
}

int WirelessTask::IsDone()
{
	return _done;
}

string WirelessTask::ToString()
{
	string str =
		string("WirelessTask { parentuuid: ") + _parentUuid +
		string("; parenttype: ") + Tools::ConvertIntToStr(_parentType) +
		string("; weekday: ") + Tools::ConvertIntToStr(_weekday) +
		string("; time: ") + ctime(&_time) +
		string("; done: ") + Tools::ConvertIntToStr(_done) +
		string(" }");
	return str;
}
