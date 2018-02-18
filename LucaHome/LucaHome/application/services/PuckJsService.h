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
#include "../../dataaccess/databases/PuckJsDatabase.h"
#include "../../domain/classes/PuckJs.h"

using namespace std;

#ifndef PUCK_JS_SERVICE_H
#define PUCK_JS_SERVICE_H

class PuckJsService
{
private:
	PuckJsDatabase _puckJsDatabase;

	string getJsonString();

	char addPuckJs(vector<string>);
	char updatePuckJs(vector<string>);
	char deletePuckJs(string);

public:
	PuckJsService();
	~PuckJsService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
