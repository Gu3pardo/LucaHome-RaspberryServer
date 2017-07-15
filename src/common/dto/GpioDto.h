#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <syslog.h>

#include "../utils/PiControl.h"
#include "../utils/Tools.h"

#ifndef GPIO_DTO_H
#define GPIO_DTO_H

class GpioDto
{
private:
	std::string _name;
	int _gpio;
	int _state;

public:
	GpioDto();
	GpioDto(std::string, int, int);
	~GpioDto();

	void SetName(std::string);
	std::string GetName();

	void SetGpio(int);
	int GetGpio();

	bool SetState(int);
	int GetState();

	std::string ToString();
};

#endif
