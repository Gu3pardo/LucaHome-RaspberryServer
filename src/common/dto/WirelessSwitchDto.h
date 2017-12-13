#include "WirelessSocketDto.h"

#ifndef SWITCH_H
#define SWITCH_H

class WirelessSwitchDto : public WirelessSocketDto
{
  protected:
	int _remoteId;
	unsigned char _keycode;
	bool _action;

  public:
	WirelessSwitchDto();
	WirelessSwitchDto(std::string, std::string, int, std::string, int, int, int, int, int, int, std::string);
	virtual ~WirelessSwitchDto();

	virtual bool SetState(int, int, int, int, int, int, int, std::string);

	bool ToggleSwitch(int, int, int, int, int, int, std::string);

	void SetRemoteId(int);
	int GetRemoteId();

	void SetKeyCode(unsigned char);
	unsigned char GetKeyCode();

	void SetAction(bool);
	bool GetAction();

	virtual std::string SaveString();
	virtual std::string JsonString();
	virtual std::string ToString();
};

#endif
