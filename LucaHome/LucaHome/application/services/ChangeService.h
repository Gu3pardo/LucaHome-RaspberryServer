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
#include "../../dataaccess/databases/ChangeDatabase.h"
#include "../../domain/classes/Change.h"

using namespace std;

#ifndef CHANGE_SERVICE_H
#define CHANGE_SERVICE_H

class ChangeService
{
private:
	ChangeDatabase _changeDatabase;

	string getJsonString();

public:
	ChangeService();
	~ChangeService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	void UpdateChange(string, string);
};

#endif
