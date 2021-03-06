#include "GpioDto.h"

GpioDto::GpioDto()
{
	_typeId = 0;
	_name = "N.A.";
	_gpio = 0;
	_state = 0;
}

GpioDto::GpioDto(int typeId, std::string name, int gpio, int state)
{
	_typeId = typeId;
	_name = name;
	_gpio = gpio;
	_state = state;
}

GpioDto::~GpioDto()
{
}

void GpioDto::SetTypeId(int typeId)
{
	_typeId = typeId;
}

int GpioDto::GetTypeId()
{
	return _typeId;
}

void GpioDto::SetName(std::string name)
{
	_name = name;
}

std::string GpioDto::GetName()
{
	return _name;
}

void GpioDto::SetGpio(int gpio)
{
	_gpio = gpio;
}

int GpioDto::GetGpio()
{
	return _gpio;
}

bool GpioDto::SetState(int state)
{
	_state = state;
	return PiControl::WriteGpio(_gpio, _state);
}

int GpioDto::GetState()
{
	return _state;
}

std::string GpioDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_typeId) + ":"
		+ _name + ":"
		+ Tools::ConvertIntToStr(_gpio) + ":"
		+ Tools::ConvertIntToStr(_state) + ";";
	return str;
}

std::string GpioDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Gpio\":")
		+ std::string("{")
		+ std::string("\"TypeId\":") + Tools::ConvertIntToStr(_typeId) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Gpio\":") + Tools::ConvertIntToStr(_gpio) + std::string(",")
		+ std::string("\"State\":") + Tools::ConvertIntToStr(_state)
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string GpioDto::ToString()
{
	std::string str =
		std::string("GpioDto { typeid: ") + Tools::ConvertIntToStr(_typeId)
		+ std::string("; name: ") + _name
		+ std::string("; gpio: ") + Tools::ConvertIntToStr(_gpio)
		+ std::string("; state: ") + Tools::ConvertIntToStr(_state)
		+ std::string(" }");
	return str;
}
