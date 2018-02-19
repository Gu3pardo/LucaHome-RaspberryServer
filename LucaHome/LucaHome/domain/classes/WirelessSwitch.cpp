#include "WirelessSwitch.h"

WirelessSwitch::WirelessSwitch() : WirelessSocket()
{
	WirelessSwitch("", "", "", 0, 0, false);
}

WirelessSwitch::WirelessSwitch(string uuid, string roomUuid, string name, int remoteId, unsigned char keycode, bool action)
	: WirelessSocket(uuid, roomUuid, name, "", false)
{
	_remoteId = remoteId;
	_keycode = keycode;
	_action = action;
}

WirelessSwitch::~WirelessSwitch()
{
}

void WirelessSwitch::SetRemoteId(int remoteId)
{
	_remoteId = remoteId;
}

int WirelessSwitch::GetRemoteId()
{
	return _remoteId;
}

void WirelessSwitch::SetKeyCode(unsigned char keycode)
{
	_keycode = keycode;
}

unsigned char WirelessSwitch::GetKeyCode()
{
	return _keycode;
}

void WirelessSwitch::SetAction(bool action)
{
	_action = action;
}

bool WirelessSwitch::GetAction()
{
	return _action;
}

string WirelessSwitch::JsonString()
{
	string str =
		string("{")
		+ string("\"WirelessSwitch\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"RemoteId\":") + Tools::ConvertIntToStr(_remoteId) + string(",")
		+ string("\"KeyCode\":") + Tools::ConvertUnsignedCharToStr(_keycode) + string(",")
		+ string("\"Action\":") + Tools::ConvertBoolToStr(_action)
		+ string("}")
		+ string("}");
	return str;
}

string WirelessSwitch::ToString()
{
	string str =
		string("WirelessSwitch { uuid: ") + _uuid
		+ string("; roomuuid: ") + _roomUuid
		+ string("; name: ") + _name
		+ string("; remoteid: ") + Tools::ConvertIntToStr(_remoteId)
		+ string("; keycode: ") + Tools::ConvertUnsignedCharToStr(_keycode)
		+ string("; action: ") + Tools::ConvertBoolToStr(_action)
		+ string(" }");
	return str;
}
