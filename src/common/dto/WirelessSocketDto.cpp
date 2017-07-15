#include "WirelessSocketDto.h"

WirelessSocketDto::WirelessSocketDto()
{
	_name = "N.A.";
	_area = "N.A.";
	_code = "N.A.";
	_state = -1;
}

WirelessSocketDto::WirelessSocketDto(std::string name, std::string area, std::string code, int state)
{
	_name = name;
	_area = area;
	_code = code;
	_state = state;
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

bool WirelessSocketDto::SetState(int state, int datagpio)
{
	_state = state;
	if (datagpio != 0)
	{
		syslog(LOG_INFO, "Set Socket %s to %d", _name.c_str(), _state);
		return PiControl::Send433Mhz(datagpio, _code, _state);
	}
	return false;
}

int WirelessSocketDto::GetState()
{
	return _state;
}

std::string WirelessSocketDto::ToString()
{
	std::string str =
		std::string("WirelessSocketDto { name: ") + _name
		+ std::string("; area: ") + _area
		+ std::string("; code: ") + _code
		+ std::string("; state: ") + Tools::ConvertIntToStr(_state)
		+ std::string(" }");
	return str;
}
