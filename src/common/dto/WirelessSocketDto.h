#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/PiControl.h"
#include "../utils/Tools.h"

#ifndef SOCKET_H
#define SOCKET_H

class WirelessSocketDto
{
  protected:
	std::string _name;
	std::string _area;
	std::string _code;
	int _state;

	int _lastTriggerHour;
	int _lastTriggerMinute;
	int _lastTriggerDay;
	int _lastTriggerMonth;
	int _lastTriggerYear;
	std::string _lastTriggerUserName;

  public:
	WirelessSocketDto();
	WirelessSocketDto(std::string, std::string, std::string, int, int, int, int, int, int, std::string);
	~WirelessSocketDto();

	void SetName(std::string);
	std::string GetName();

	void SetArea(std::string);
	std::string GetArea();

	void SetCode(std::string);
	std::string GetCode();

	int GetLastTriggeredHour();
	int GetLastTriggeredMinute();
	int GetLastTriggeredDay();
	int GetLastTriggeredMonth();
	int GetLastTriggeredYear();
	std::string GetLastTriggeredUserName();

	bool SetState(int, int, int, int, int, int, int, std::string);
	int GetState();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
