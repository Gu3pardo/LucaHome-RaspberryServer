#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../crosscutting/controller/MailController.h"
#include "../../domain/classes/Room.h"
#include "../../domain/classes/Temperature.h"

using namespace std;

#ifndef TEMPERATURE_SERVICE_H
#define TEMPERATURE_SERVICE_H

class TemperatureService
{
private:
	Room _room;
	string _sensorPath;
	string _graphPath;

	int _minTemp;
	int _maxTemp;

	int _warningCount;
	bool _isInitialized;

	string getJsonString();
	double loadTemperature();
	void sendWarningMail(string);

public:
	TemperatureService();
	~TemperatureService();

	void Initialize(Room, string, string, int, int);
	string PerformAction(vector<string>);

	void CheckTemperature();
};

#endif
