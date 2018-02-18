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
#include "../../dataaccess/databases/MediaServerDatabase.h"
#include "../../domain/classes/MediaServer.h"

using namespace std;

#ifndef MEDIA_SERVER_SERVICE_H
#define MEDIA_SERVER_SERVICE_H

class MediaServerService
{
private:
	MediaServerDatabase _mediaServerDatabase;

	string getJsonString();

	char addMediaServer(vector<string>);
	char updateMediaServer(vector<string>);
	char deleteMediaServer(string);

public:
	MediaServerService();
	~MediaServerService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
