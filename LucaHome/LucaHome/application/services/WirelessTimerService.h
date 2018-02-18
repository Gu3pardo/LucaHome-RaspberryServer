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
#include "../../dataaccess/databases/WirelessTimerDatabase.h"
#include "../../domain/classes/WirelessTimer.h"

using namespace std;

#ifndef WIRELESS_TIMER_SERVICE_H
#define WIRELESS_TIMER_SERVICE_H

class WirelessTimerService
{
private:
	WirelessTimerDatabase _wirelessTimerDatabase;

	string getJsonString();

	char addWirelessTimer(vector<string>);
	char updateWirelessTimer(vector<string>);
	char deleteWirelessTimer(string);

public:
	WirelessTimerService();
	~WirelessTimerService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	vector<WirelessTimer> GetWirelessTimerList();
};

#endif
