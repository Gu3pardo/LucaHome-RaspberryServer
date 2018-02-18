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
#include "../../dataaccess/databases/MapContentDatabase.h"
#include "../../domain/classes/MapContent.h"

using namespace std;

#ifndef MAP_CONTENT_SERVICE_H
#define MAP_CONTENT_SERVICE_H

class MapContentService
{
private:
	MapContentDatabase _mapContentDatabase;

	string getJsonString();

	char addMapContent(vector<string>);
	char updateMapContent(vector<string>);
	char deleteMapContent(string);

public:
	MapContentService();
	~MapContentService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
