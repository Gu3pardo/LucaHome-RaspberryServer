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
#include "../../dataaccess/databases/RadioStreamDatabase.h"
#include "../../domain/classes/RadioStream.h"

using namespace std;

#ifndef RADIO_STREAM_SERVICE_H
#define RADIO_STREAM_SERVICE_H

class RadioStreamService
{
private:
	RadioStreamDatabase _radioStreamDatabase;

	string getJsonString();

	char addRadioStream(vector<string>);
	char updateRadioStream(vector<string>);
	char deleteRadioStream(string);

public:
	RadioStreamService();
	~RadioStreamService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
