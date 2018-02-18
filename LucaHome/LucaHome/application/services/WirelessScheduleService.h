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
#include "../../dataaccess/databases/WirelessScheduleDatabase.h"
#include "../../domain/classes/WirelessSchedule.h"

using namespace std;

#ifndef WIRELESS_SCHEDULE_SERVICE_H
#define WIRELESS_SCHEDULE_SERVICE_H

class WirelessScheduleService
{
private:
	WirelessScheduleDatabase _wirelessScheduleDatabase;

	string getJsonString();

	char addWirelessSchedule(vector<string>);
	char updateWirelessSchedule(vector<string>);
	char deleteWirelessSchedule(string);
	char setWirelessSchedule(vector<string>);

public:
	WirelessScheduleService();
	~WirelessScheduleService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	vector<WirelessSchedule> GetWirelessScheduleList();
};

#endif
