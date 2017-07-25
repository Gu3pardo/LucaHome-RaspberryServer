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
  private:
	std::string _name;
	std::string _area;
	std::string _code;
	int _state;

  public:
	WirelessSocketDto();
	WirelessSocketDto(std::string, std::string, std::string, int);
	~WirelessSocketDto();

	void SetName(std::string);
	std::string GetName();

	void SetArea(std::string);
	std::string GetArea();

	void SetCode(std::string);
	std::string GetCode();

	bool SetState(int, int);
	int GetState();

	std::string ToString();
};

#endif
