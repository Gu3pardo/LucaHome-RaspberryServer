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
#include "../../dataaccess/databases/ApplicationInformationDatabase.h"
#include "../../domain/classes/ApplicationInformation.h"

using namespace std;

#ifndef APPLICATION_INFORMATION_SERVICE_H
#define APPLICATION_INFORMATION_SERVICE_H

class ApplicationInformationService
{
private:
	ApplicationInformationDatabase _applicationInformationDatabase;

	string getJsonString();

	char addApplicationInformation(vector<string>);
	char updateApplicationInformation(vector<string>);
	char deleteApplicationInformation(string);

public:
	ApplicationInformationService();
	~ApplicationInformationService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
