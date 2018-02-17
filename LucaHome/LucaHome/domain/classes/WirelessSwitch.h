#include "WirelessSocket.h"

#ifndef WIRELESS_SWITCH_H
#define WIRELESS_SWITCH_H

class WirelessSwitch : public WirelessSocket
{
private:
	int _remoteId;
	unsigned char _keycode;
	bool _action;

public:
	WirelessSwitch();
	WirelessSwitch(string, string, string, int, unsigned char, bool);
	virtual ~WirelessSwitch();

	void SetRemoteId(int);
	int GetRemoteId();

	void SetKeyCode(unsigned char);
	unsigned char GetKeyCode();

	void SetAction(bool);
	bool GetAction();

	virtual string JsonString();
	virtual string ToString();
};

#endif
