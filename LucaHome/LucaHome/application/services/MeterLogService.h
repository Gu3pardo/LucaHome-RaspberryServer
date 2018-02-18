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
#include "../../dataaccess/databases/MeterLogItemDatabase.h"
#include "../../domain/classes/MeterLogItem.h"

using namespace std;

#ifndef METER_LOG_SERVICE_H
#define METER_LOG_SERVICE_H

class MeterLogService
{
private:
	MeterLogItemDatabase _meterLogItemDatabase;

	string getJsonString();

	char addMeterLogItem(vector<string>);
	char updateMeterLogItem(vector<string>);
	char deleteMeterLogItem(string);

public:
	MeterLogService();
	~MeterLogService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
