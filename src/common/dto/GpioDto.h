#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/PiControl.h"
#include "../utils/Tools.h"

#ifndef GPIO_DTO_H
#define GPIO_DTO_H

class GpioDto
{
private:
	int _typeId;
	std::string _name;
	int _gpio;
	int _state;

public:
	GpioDto();
	GpioDto(int, std::string, int, int);
	~GpioDto();

	void SetTypeId(int);
	int GetTypeId();

	void SetName(std::string);
	std::string GetName();

	void SetGpio(int);
	int GetGpio();

	bool SetState(int);
	int GetState();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
