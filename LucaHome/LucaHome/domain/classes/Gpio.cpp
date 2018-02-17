#include "Gpio.h"

Gpio::Gpio()
{
	_uuid = "";
	_name = "";
	_pin = 0;
	_state = false;
}

Gpio::Gpio(string uuid, string name, int pin, bool state)
{
	_uuid = uuid;
	_name = name;
	_pin = pin;
	_state = state;
}

Gpio::~Gpio()
{
}

void Gpio::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Gpio::GetUuid()
{
	return _uuid;
}

void Gpio::SetName(string name)
{
	_name = name;
}

string Gpio::GetName()
{
	return _name;
}

void Gpio::SetPin(int pin)
{
	_pin = pin;
}

int Gpio::GetPin()
{
	return _pin;
}

void Gpio::SetState(bool state)
{
	_state = state;
}

bool Gpio::GetState()
{
	return _state;
}

string Gpio::JsonString()
{
	string str =
		string("{")
		+ string("\"Gpio\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Pin\":") + Tools::ConvertIntToStr(_pin) + string(",")
		+ string("\"State\":") + Tools::ConvertBoolToStr(_state)
		+ string("}")
		+ string("}");
	return str;
}

string Gpio::ToString()
{
	string str =
		string("Gpio { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; pin: ") + Tools::ConvertIntToStr(_pin)
		+ string("; state: ") + Tools::ConvertBoolToStr(_state)
		+ string(" }");
	return str;
}
