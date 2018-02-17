#include "WirelessTimer.h"

WirelessTimer::WirelessTimer() : WirelessSchedule()
{
}

WirelessTimer::WirelessTimer(
	string uuid, string name,
	int weekday, int hour, int minute,
	string wirelessSocketUuid, bool wirelessSocketAction,
	string wirelessSwitchUuid)
	: WirelessSchedule(
		uuid, name,
		weekday, hour, minute,
		true,
		wirelessSocketUuid, wirelessSocketAction,
		wirelessSwitchUuid)
{
}

WirelessTimer::~WirelessTimer()
{
}

string WirelessTimer::JsonString()
{
	string str =
		string("{")
		+ string("\"WirelessTimer\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Weekday\":") + Tools::ConvertIntToStr(_weekday) + string(",")
		+ string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + string(",")
		+ string("\"Minute\":") + Tools::ConvertIntToStr(_minute) + string(",")
		+ string("\"IsActive\":") + Tools::ConvertIntToStr(_isActive) + string(",")
		+ string("\"WirelessSocketUuid\":\"") + _wirelessSocketUuid + string("\",")
		+ string("\"WirelessSocketAction\":") + Tools::ConvertBoolToStr(_wirelessSocketAction) + string(",")
		+ string("\"WirelessSwitchUuid\":\"") + _wirelessSwitchUuid
		+ string("}")
		+ string("}");
	return str;
}

string WirelessTimer::ToString()
{
	string str = string("WirelessTimer { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ string("; time: ") + Tools::ConvertIntToStr(_hour) + string(":") + Tools::ConvertIntToStr(_minute)
		+ string("; isactive: ") + Tools::ConvertIntToStr(_isActive)
		+ string("; wirelesssocketuuid: ") + _wirelessSocketUuid
		+ string("; wirelesssocketaction: ") + Tools::ConvertBoolToStr(_wirelessSocketAction)
		+ string("; wirelessswitchuuid: ") + _wirelessSwitchUuid
		+ string(" }");
	return str;
}
