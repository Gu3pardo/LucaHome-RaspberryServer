#include "ScheduleDto.h"

ScheduleDto::ScheduleDto()
{
	_name = "N.A.";
	_socket = "N.A.";
	_gpio = "N.A.";
	_switch = "N.A.";
	_weekday = 0;
	_hour = 0;
	_minute = 0;
	_onoff = 0;
	_isTimer = false;
	_state = 0;
}

ScheduleDto::ScheduleDto(
	std::string name,
	std::string socket,
	std::string gpio,
	std::string switchName,
	int weekday,
	int hour,
	int minute,
	int onoff,
	bool isTimer,
	int state)
{
	_name = name;
	_socket = socket;
	_gpio = gpio;
	_switch = switchName;
	_weekday = weekday;
	_hour = hour;
	_minute = minute;
	_onoff = onoff;
	_isTimer = isTimer;
	_state = state;
}

ScheduleDto::~ScheduleDto()
{
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

void ScheduleDto::SetOnoff(int onoff)
{
	_onoff = onoff;
}

int ScheduleDto::GetOnoff()
{
	return _onoff;
}

void ScheduleDto::SetIsTimer(int isTimer)
{
	_isTimer = isTimer;
}

int ScheduleDto::GetIsTimer()
{
	return _isTimer;
}

bool ScheduleDto::SetState(int state)
{
	_state = state;
	return true;
}

int ScheduleDto::GetState()
{
	return _state;
}

std::string ScheduleDto::SaveString()
{
	std::string str = 
		_name + ":"
		+ _socket + ":"
		+ _gpio + ":"
		+ _switch + ":"
		+ Tools::ConvertIntToStr(_weekday) + ":"
		+ Tools::ConvertIntToStr(_hour) + ":"
		+ Tools::ConvertIntToStr(_minute) + ":"
		+ Tools::ConvertIntToStr(_onoff) + ":"
		+ Tools::ConvertBoolToStr(_isTimer) + ":"
		+ Tools::ConvertIntToStr(_state) + ";";
	return str;
}

std::string ScheduleDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Schedule\":")
		+ std::string("{")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Socket\":\"") + _socket + std::string("\",")
		+ std::string("\"Gpio\":\"") + _gpio + std::string("\",")
		+ std::string("\"Switch\":\"") + _switch + std::string("\",")
		+ std::string("\"Weekday\":") + Tools::ConvertIntToStr(_weekday) + std::string(",")
		+ std::string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + std::string(",")
		+ std::string("\"Minute\":") + Tools::ConvertIntToStr(_minute) + std::string(",")
		+ std::string("\"OnOff\":") + Tools::ConvertIntToStr(_onoff) + std::string(",")
		+ std::string("\"IsTimer\":") + Tools::ConvertBoolToStr(_isTimer) + std::string(",")
		+ std::string("\"State\":") + Tools::ConvertIntToStr(_state)
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string ScheduleDto::ToString()
{
	std::string str = std::string("ScheduleDto { name: ") + _name
		+ std::string("; socket: ") + _socket
		+ std::string("; gpio: ") + _gpio
		+ std::string("; switch: ") + _switch
		+ std::string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ std::string("; time: ") + Tools::ConvertIntToStr(_hour)
		+ std::string(":") + Tools::ConvertIntToStr(_minute)
		+ std::string("; onoff: ") + Tools::ConvertIntToStr(_onoff)
		+ std::string("; isTimer: ") + Tools::ConvertBoolToStr(_isTimer)
		+ std::string("; state: ") + Tools::ConvertIntToStr(_state)
		+ std::string(" }");
	return str;
}