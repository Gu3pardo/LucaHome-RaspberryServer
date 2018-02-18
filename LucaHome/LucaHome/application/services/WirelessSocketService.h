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
#include "../../dataaccess/databases/WirelessSocketDatabase.h"
#include "../../domain/classes/WirelessSocket.h"

using namespace std;

#ifndef WIRELESS_SOCKET_SERVICE_H
#define WIRELESS_SOCKET_SERVICE_H

class WirelessSocketService
{
private:
	WirelessSocketDatabase _wirelessSocketDatabase;

	string getJsonString();

	char addWirelessSocket(vector<string>);
	char updateWirelessSocket(vector<string>);
	char deleteWirelessSocket(string);
	char setWirelessSocket(vector<string>);

public:
	WirelessSocketService();
	~WirelessSocketService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	vector<WirelessSocket> GetWirelessSocketList();
};

#endif
