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
#include "../../dataaccess/databases/WirelessSwitchDatabase.h"
#include "../../domain/classes/WirelessSwitch.h"

using namespace std;

#ifndef WIRELESS_SWITCH_SERVICE_H
#define WIRELESS_SWITCH_SERVICE_H

class WirelessSwitchService
{
private:
	WirelessSwitchDatabase _wirelessSwitchDatabase;

	string getJsonString();

	char addWirelessSwitch(vector<string>);
	char updateWirelessSwitch(vector<string>);
	char deleteWirelessSwitch(string);
	char toggleWirelessSwitch(vector<string>);

public:
	WirelessSwitchService();
	~WirelessSwitchService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	vector<WirelessSwitch> GetWirelessSwitchList();
};

#endif
