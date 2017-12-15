#include "WirelessSwitchDto.h"

WirelessSwitchDto::WirelessSwitchDto()
	: WirelessSocketDto()
{
	_remoteId = -1;
	_keycode = -1;
	_action = false;
}

WirelessSwitchDto::WirelessSwitchDto(std::string name, std::string area, int remoteId, std::string keycode, int state, int lastTriggerHour, int lastTriggerMinute, int lastTriggerDay, int lastTriggerMonth, int lastTriggerYear, std::string lastTriggerUserName)
	: WirelessSocketDto(name, area, keycode, state, lastTriggerHour, lastTriggerMinute, lastTriggerDay, lastTriggerMonth, lastTriggerYear, lastTriggerUserName)
{
	_remoteId = remoteId;
	_keycode = Tools::ConvertStrToUnsignedChar(keycode);
	_action = false;
}

WirelessSwitchDto::~WirelessSwitchDto()
{
}

bool WirelessSwitchDto::SetState(int state, int datagpio, int lastTriggerHour, int lastTriggerMinute, int lastTriggerDay, int lastTriggerMonth, int lastTriggerYear, std::string lastTriggerUserName)
{
	return false;
}

bool WirelessSwitchDto::ToggleSwitch(int datagpio, int lastTriggerHour, int lastTriggerMinute, int lastTriggerDay, int lastTriggerMonth, int lastTriggerYear, std::string lastTriggerUserName)
{
	if (datagpio != 0 && _remoteId != -1 && _keycode != -1) {
		if (PiControl::SendButton(_remoteId, _keycode, datagpio, _action)) {
			_action = !_action;

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

void WirelessSwitchDto::SetRemoteId(int remoteId)
{
	_remoteId = remoteId;
}

int WirelessSwitchDto::GetRemoteId()
{
	return _remoteId;
}

void WirelessSwitchDto::SetKeyCode(unsigned char keycode)
{
	_keycode = keycode;
}

unsigned char WirelessSwitchDto::GetKeyCode()
{
	return _keycode;
}

void WirelessSwitchDto::SetAction(bool action)
{
	_action = action;
}

bool WirelessSwitchDto::GetAction()
{
	return _action;
}

std::string WirelessSwitchDto::SaveString()
{
	std::string str =
		_name + ":"
		+ _area + ":"
		+ Tools::ConvertIntToStr(_remoteId) + ":"
		+ Tools::ConvertUnsignedCharToStr(_keycode) + ":"
		+ Tools::ConvertBoolToStr(_action) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerHour) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerMinute) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerDay) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerMonth) + ":"
		+ Tools::ConvertIntToStr(_lastTriggerYear) + ":"
		+ _lastTriggerUserName + ";";
	return str;
}

std::string WirelessSwitchDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"WirelessSwitch\":")
		+ std::string("{")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Area\":\"") + _area + std::string("\",")
		+ std::string("\"RemoteId\":") + Tools::ConvertIntToStr(_remoteId) + std::string(",")
		+ std::string("\"KeyCode\":") + Tools::ConvertUnsignedCharToStr(_keycode) + std::string(",")
		+ std::string("\"Action\":") + Tools::ConvertBoolToStr(_action) + std::string(",")
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

std::string WirelessSwitchDto::ToString()
{
	std::string str =
		std::string("WirelessSwitchDto { name: ") + _name
		+ std::string("; area: ") + _area
		+ std::string("; remoteid: ") + Tools::ConvertIntToStr(_remoteId)
		+ std::string("; keycode: ") + Tools::ConvertUnsignedCharToStr(_keycode)
		+ std::string("; action: ") + Tools::ConvertBoolToStr(_action)
		+ std::string("; hour: ") + Tools::ConvertIntToStr(_lastTriggerHour)
		+ std::string("; minute: ") + Tools::ConvertIntToStr(_lastTriggerMinute)
		+ std::string("; day: ") + Tools::ConvertIntToStr(_lastTriggerDay)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_lastTriggerMonth)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_lastTriggerYear)
		+ std::string("; userName: ") + _lastTriggerUserName
		+ std::string(" }");
	return str;
}
