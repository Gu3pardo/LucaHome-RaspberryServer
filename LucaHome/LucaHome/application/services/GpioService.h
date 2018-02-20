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
#include "../../crosscutting/utils.h"
#include "../../dataaccess/databases/GpioDatabase.h"
#include "../../domain/classes/Gpio.h"

using namespace std;

#ifndef GPIO_SERVICE_H
#define GPIO_SERVICE_H

class GpioService
{
private:
	GpioDatabase _gpioDatabase;

	string getJsonString();

	char addGpio(vector<string>);
	char updateGpio(vector<string>);
	char deleteGpio(string);
	char setGpio(vector<string>);

public:
	GpioService();
	~GpioService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
