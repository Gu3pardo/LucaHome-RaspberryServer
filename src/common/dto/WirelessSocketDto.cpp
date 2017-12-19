#include "WirelessSocketDto.h"

WirelessSocketDto::WirelessSocketDto()
{
	_name = "N.A.";
	_area = "N.A.";
	_code = "N.A.";
	_state = 0;

	_lastTriggerHour = 0;
	_lastTriggerMinute = 0;
	_lastTriggerDay = 1;
	_lastTriggerMonth = 1;
	_lastTriggerYear = 1970;
	_lastTriggerUserName = "N.A.";
}

WirelessSocketDto::WirelessSocketDto(std::string name, std::string area, std::string code, int state, int lastTriggerHour, int lastTriggerMinute, int lastTriggerDay, int lastTriggerMonth, int lastTriggerYear, std::string lastTriggerUserName)
{
	_name = name;
	_area = area;
	_code = code;
	_state = state;

	_lastTriggerHour = lastTriggerHour;
	_lastTriggerMinute = lastTriggerMinute;
	_lastTriggerDay = lastTriggerDay;
	_lastTriggerMonth = lastTriggerMonth;
	_lastTriggerYear = lastTriggerYear;
	_lastTriggerUserName = lastTriggerUserName;
}

WirelessSocketDto::~WirelessSocketDto()
{
}

void WirelessSocketDto::SetName(std::string name)
{
	_name = name;
}

std::string WirelessSocketDto::GetName()
{
	return _name;
}

void WirelessSocketDto::SetArea(std::string area)
{
	_area = area;
}

std::string WirelessSocketDto::GetArea()
{
	return _area;
}

void WirelessSocketDto::SetCode(std::string code)
{
	_code = code;
}

std::string WirelessSocketDto::GetCode()
{
	return _code;
}

int WirelessSocketDto::GetLastTriggeredHour()
{
	return _lastTriggerHour;
}

int WirelessSocketDto::GetLastTriggeredMinute()
{
	return _lastTriggerMinute;
}

int WirelessSocketDto::GetLastTriggeredDay()
{
	return _lastTriggerDay;
}

int WirelessSocketDto::GetLastTriggeredMonth()
{
	return _lastTriggerMonth;
}

int WirelessSocketDto::GetLastTriggeredYear()
{
	return _lastTriggerYear;
}

std::string WirelessSocketDto::GetLastTriggeredUserName()
{
	return _lastTriggerUserName;
}

bool WirelessSocketDto::SetState(int state, int datagpio, int lastTriggerHour, int lastTriggerMinute, int lastTriggerDay, int lastTriggerMonth, int lastTriggerYear, std::string lastTriggerUserName)
{
	if (datagpio != 0)
	{
		if (PiControl::Send433Mhz(datagpio, _code, state)) {
			_state = state;

			_lastTriggerHour = lastTriggerHour;
			_lastTriggerMinute = lastTriggerMinute;
			_lastTriggerDay = lastTriggerDay;
			_lastTriggerMonth = lastTriggerMonth;
			_lastTriggerYear = lastTriggerYear;
			_lastTriggerUserName = lastTriggerUserName;

			return true;
		}
	}
	return false;
}

int WirelessSocketDto::GetState()
{
	return _state;
}

std::string WirelessSocketDto::SaveString()
{
	std::string str = 
		_name + ":"
		+ _area + ":"
		+ _code + ":"
		+ Tools::ConvertIntToStr(_state) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerHour) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerMinute) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerDay) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerMonth) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerYear) + ":"
		+ _lastTriggerUserName + ";";
	return str;
}

std::string WirelessSocketDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"WirelessSocket\":")
		+ std::string("{")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Area\":\"") + _area + std::string("\",")
		+ std::string("\"Code\":\"") + _code + std::string("\",")
		+ std::string("\"State\":") + Tools::ConvertIntToStr(_state) + std::string(",")
		+ std::string("\"LastTrigger\":")
		+ std::string("{")
		+ std::string("\"Hour\":") + Tools::ConvertIntToStr(_lastTriggerHour) + std::string(",")
		+ std::string("\"Minute\":") + Tools::ConvertIntToStr(_lastTriggerMinute) + std::string(",")
		+ std::string("\"Day\":") + Tools::ConvertIntToStr(_lastTriggerDay) + std::string(",")
		+ std::string("\"Month\":") + Tools::ConvertIntToStr(_lastTriggerMonth) + std::string(",")
		+ std::string("\"Year\":") + Tools::ConvertIntToStr(_lastTriggerYear) + std::string(",")
		+ std::string("\"UserName\":\"") + _lastTriggerUserName
		+ std::string("\"}")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string WirelessSocketDto::ToString()
{
	std::string str =
		std::string("WirelessSocketDto { name: ") + _name
		+ std::string("; area: ") + _area
		+ std::string("; code: ") + _code
		+ std::string("; state: ") + Tools::ConvertIntToStr(_state)
		+ std::string("; hour: ") + Tools::ConvertIntToStr(_lastTriggerHour)
		+ std::string("; minute: ") + Tools::ConvertIntToStr(_lastTriggerMinute)
		+ std::string("; day: ") + Tools::ConvertIntToStr(_lastTriggerDay)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_lastTriggerMonth)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_lastTriggerYear)
		+ std::string("; userName: ") + _lastTriggerUserName
		+ std::string(" }");
	return str;
}
