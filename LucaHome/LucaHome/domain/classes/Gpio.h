#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef GPIO_H
#define GPIO_H

class Gpio
{
private:
	string _uuid;
	string _name;
	int _pin;
	bool _state;

public:
	Gpio();
	Gpio(string, string, int, bool);
	~Gpio();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetPin(int);
	int GetPin();

	void SetState(bool);
	bool GetState();

	string JsonString();
	string ToString();
};

#endif
