#include "ScheduleDto.h"

ScheduleDto::ScheduleDto()
{
	_name = "N.A.";
	_socket = "N.A.";
	_gpio = "N.A.";
	_weekday = -1;
	_hour = -1;
	_minute = -1;
	_onoff = -1;
	_isTimer = -1;
	_playSound = -1;
	_playRaspberry = -1;
	_status = -1;
}

ScheduleDto::ScheduleDto(
		std::string name,
		std::string socket,
		std::string gpio,
		int weekday,
		int hour,
		int minute,
		int onoff,
		int isTimer,
		int playSound,
		int playRaspberry,
		int status)
{
	_name = name;
	_socket = socket;
	_gpio = gpio;
	_weekday = weekday;
	_hour = hour;
	_minute = minute;
	_onoff = onoff;
	_isTimer = isTimer;
	_playSound = playSound;
	_playRaspberry = playRaspberry;
	_status = status;
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

void ScheduleDto::SetPlaySound(int playSound)
{
	_playSound = playSound;
}

int ScheduleDto::GetPlaySound()
{
	return _playSound;
}

void ScheduleDto::SetPlayRaspberry(int playRaspberry)
{
	_playRaspberry = playRaspberry;
}

int ScheduleDto::GetPlayRaspberry()
{
	return _playRaspberry;
}

bool ScheduleDto::SetStatus(int status)
{
	_status = status;
	return true;
}

int ScheduleDto::GetStatus()
{
	return _status;
}

std::string ScheduleDto::ToString()
{
	std::string str =
			std::string("ScheduleDto { name: ") + _name 
		+ std::string("; socket: ") + _socket 
		+ std::string("; gpio: ") + _gpio 
		+ std::string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ std::string("; time: ") + Tools::ConvertIntToStr(_hour)
		+ std::string(":") + Tools::ConvertIntToStr(_minute)
		+ std::string("; onoff: ") + Tools::ConvertIntToStr(_onoff)
		+ std::string("; isTimer: ") + Tools::ConvertIntToStr(_isTimer)
		+ std::string("; playSound: ") + Tools::ConvertIntToStr(_playSound)
		+ std::string("; playRaspberry: ") + Tools::ConvertIntToStr(_playRaspberry)
		+ std::string("; status: ") + Tools::ConvertIntToStr(_status)
		+ std::string(" }");
	return str;
}