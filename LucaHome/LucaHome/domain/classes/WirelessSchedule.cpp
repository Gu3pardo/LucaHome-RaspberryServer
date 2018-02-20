#include "WirelessSchedule.h"

WirelessSchedule::WirelessSchedule()
{
	WirelessSchedule("", "", 0, 0, 0, false, "", false, "", false, "");
}

WirelessSchedule::WirelessSchedule(
	string uuid, string name,
	int weekday, int hour, int minute,
	bool isActive,
	string gpioUuid, bool gpioAction,
	string wirelessSocketUuid, bool wirelessSocketAction,
	string wirelessSwitchUuid)
{
	_uuid = uuid;
	_name = name;
	_weekday = weekday;
	_hour = hour;
	_minute = minute;
	_isActive = isActive;
	_gpioUuid = gpioUuid;
	_gpioAction = gpioAction;
	_wirelessSocketUuid = wirelessSocketUuid;
	_wirelessSocketAction = wirelessSocketAction;
	_wirelessSwitchUuid = wirelessSwitchUuid;
}

WirelessSchedule::~WirelessSchedule()
{
}

void WirelessSchedule::SetUuid(string uuid)
{
	_uuid = uuid;
}

string WirelessSchedule::GetUuid()
{
	return _uuid;
}

void WirelessSchedule::SetName(string name)
{
	_name = name;
}

string WirelessSchedule::GetName()
{
	return _name;
}

void WirelessSchedule::SetWeekday(int weekday)
{
	_weekday = weekday;
}

int WirelessSchedule::GetWeekday()
{
	return _weekday;
}

void WirelessSchedule::SetHour(int hour)
{
	_hour = hour;
}

int WirelessSchedule::GetHour()
{
	return _hour;
}

void WirelessSchedule::SetMinute(int minute)
{
	_minute = minute;
}

int WirelessSchedule::GetMinute()
{
	return _minute;
}

void WirelessSchedule::SetActive(bool isActive)
{
	_isActive = isActive;
}

bool WirelessSchedule::IsActive()
{
	return _isActive;
}

void WirelessSchedule::SetGpioUuid(string gpioUuid)
{
	_gpioUuid = gpioUuid;
}

string WirelessSchedule::GetGpioUuid()
{
	return _gpioUuid;
}

void WirelessSchedule::SetGpioAction(bool gpioAction)
{
	_gpioAction = gpioAction;
}

bool WirelessSchedule::GetGpioAction()
{
	return _gpioAction;
}

void WirelessSchedule::SetWirelessSocketUuid(string wirelessSocketUuid)
{
	_wirelessSocketUuid = wirelessSocketUuid;
}

string WirelessSchedule::GetWirelessSocketUuid()
{
	return _wirelessSocketUuid;
}

void WirelessSchedule::SetWirelessSocketAction(bool wirelessSocketAction)
{
	_wirelessSocketAction = wirelessSocketAction;
}

bool WirelessSchedule::GetWirelessSocketAction()
{
	return _wirelessSocketAction;
}

void WirelessSchedule::SetWirelessSwitchUuid(string wirelessSwitchUuid)
{
	_wirelessSwitchUuid = wirelessSwitchUuid;
}

string WirelessSchedule::GetWirelessSwitchUuid()
{
	return _wirelessSwitchUuid;
}

string WirelessSchedule::JsonString()
{
	string str =
		string("{")
		+ string("\"WirelessSchedule\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Weekday\":") + Tools::ConvertIntToStr(_weekday) + string(",")
		+ string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + string(",")
		+ string("\"Minute\":") + Tools::ConvertIntToStr(_minute) + string(",")
		+ string("\"IsActive\":") + Tools::ConvertIntToStr(_isActive) + string(",")
		+ string("\"GpioUuid\":\"") + _gpioUuid + string("\",")
		+ string("\"GpioAction\":") + Tools::ConvertBoolToStr(_gpioAction) + string(",")
		+ string("\"WirelessSocketUuid\":\"") + _wirelessSocketUuid + string("\",")
		+ string("\"WirelessSocketAction\":") + Tools::ConvertBoolToStr(_wirelessSocketAction) + string(",")
		+ string("\"WirelessSwitchUuid\":\"") + _wirelessSwitchUuid
		+ string("}")
		+ string("}");
	return str;
}

string WirelessSchedule::ToString()
{
	string str = string("WirelessSchedule { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ string("; time: ") + Tools::ConvertIntToStr(_hour) + string(":") + Tools::ConvertIntToStr(_minute)
		+ string("; isactive: ") + Tools::ConvertIntToStr(_isActive)
		+ string("; gpiouuid: ") + _gpioUuid
		+ string("; gpioaction: ") + Tools::ConvertBoolToStr(_gpioAction)
		+ string("; wirelesssocketuuid: ") + _wirelessSocketUuid
		+ string("; wirelesssocketaction: ") + Tools::ConvertBoolToStr(_wirelessSocketAction)
		+ string("; wirelessswitchuuid: ") + _wirelessSwitchUuid
		+ string(" }");
	return str;
}