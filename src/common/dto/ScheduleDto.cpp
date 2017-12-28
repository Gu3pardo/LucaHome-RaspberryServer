#include "ScheduleDto.h"

ScheduleDto::ScheduleDto()
{
	_id = 0;
	_name = "N.A.";
	_socket = "N.A.";
	_gpio = "N.A.";
	_switch = "N.A.";
	_weekday = 0;
	_hour = 0;
	_minute = 0;
	_action = false;
	_isTimer = false;
	_isActive = false;
}

ScheduleDto::ScheduleDto(
	int id,
	std::string name,
	std::string socket,
	std::string gpio,
	std::string switchName,
	int weekday,
	int hour,
	int minute,
	bool action,
	bool isTimer,
	bool isActive)
{
	_id = id;
	_name = name;
	_socket = socket;
	_gpio = gpio;
	_switch = switchName;
	_weekday = weekday;
	_hour = hour;
	_minute = minute;
	_action = action;
	_isTimer = isTimer;
	_isActive = isActive;
}

ScheduleDto::~ScheduleDto()
{
}

void ScheduleDto::SetId(int id)
{
	_id = id;
}

int ScheduleDto::GetId()
{
	return _id;
}

void ScheduleDto::SetName(std::string name)
{
	_name = name;
}

std::string ScheduleDto::GetName()
{
	return _name;
}

void ScheduleDto::SetSocket(std::string socket)
{
	_socket = socket;
}

std::string ScheduleDto::GetSocket()
{
	return _socket;
}

void ScheduleDto::SetGpio(std::string gpio)
{
	_gpio = gpio;
}

std::string ScheduleDto::GetGpio()
{
	return _gpio;
}

void ScheduleDto::SetSwitch(std::string switchName)
{
	_switch = switchName;
}

std::string ScheduleDto::GetSwitch()
{
	return _switch;
}

void ScheduleDto::SetWeekday(int weekday)
{
	_weekday = weekday;
}

int ScheduleDto::GetWeekday()
{
	return _weekday;
}

void ScheduleDto::SetHour(int hour)
{
	_hour = hour;
}

int ScheduleDto::GetHour()
{
	return _hour;
}

void ScheduleDto::SetMinute(int minute)
{
	_minute = minute;
}

int ScheduleDto::GetMinute()
{
	return _minute;
}

void ScheduleDto::SetAction(bool action)
{
	_action = action;
}

bool ScheduleDto::GetAction()
{
	return _action;
}

void ScheduleDto::SetIsTimer(bool isTimer)
{
	_isTimer = isTimer;
}

bool ScheduleDto::GetIsTimer()
{
	return _isTimer;
}

void ScheduleDto::SetIsActive(bool isActive)
{
	_isActive = isActive;
}

bool ScheduleDto::GetIsActive()
{
	return _isActive;
}

std::string ScheduleDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _name + ":"
		+ _socket + ":"
		+ _gpio + ":"
		+ _switch + ":"
		+ Tools::ConvertIntToStr(_weekday) + ":"
		+ Tools::ConvertIntToStr(_hour) + ":"
		+ Tools::ConvertIntToStr(_minute) + ":"
		+ Tools::ConvertBoolToStr(_action) + ":"
		+ Tools::ConvertBoolToStr(_isTimer) + ":"
		+ Tools::ConvertBoolToStr(_isActive) + ";";
	return str;
}

std::string ScheduleDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Schedule\":")
		+ std::string("{")
		+ std::string("\"Id\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Socket\":\"") + _socket + std::string("\",")
		+ std::string("\"Gpio\":\"") + _gpio + std::string("\",")
		+ std::string("\"Switch\":\"") + _switch + std::string("\",")
		+ std::string("\"Weekday\":") + Tools::ConvertIntToStr(_weekday) + std::string(",")
		+ std::string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + std::string(",")
		+ std::string("\"Minute\":") + Tools::ConvertIntToStr(_minute) + std::string(",")
		+ std::string("\"Action\":") + Tools::ConvertIntToStr(_action) + std::string(",")
		+ std::string("\"IsTimer\":") + Tools::ConvertBoolToStr(_isTimer) + std::string(",")
		+ std::string("\"IsActive\":") + Tools::ConvertIntToStr(_isActive)
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string ScheduleDto::ToString()
{
	std::string str = std::string("ScheduleDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; name: ") + _name
		+ std::string("; socket: ") + _socket
		+ std::string("; gpio: ") + _gpio
		+ std::string("; switch: ") + _switch
		+ std::string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ std::string("; time: ") + Tools::ConvertIntToStr(_hour)
		+ std::string(":") + Tools::ConvertIntToStr(_minute)
		+ std::string("; action: ") + Tools::ConvertIntToStr(_action)
		+ std::string("; isTimer: ") + Tools::ConvertBoolToStr(_isTimer)
		+ std::string("; isActive: ") + Tools::ConvertIntToStr(_isActive)
		+ std::string(" }");
	return str;
}