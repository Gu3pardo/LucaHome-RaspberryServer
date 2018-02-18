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
#include "../../dataaccess/databases/RssFeedDatabase.h"
#include "../../domain/classes/RssFeed.h"

using namespace std;

#ifndef RSS_FEED_SERVICE_H
#define RSS_FEED_SERVICE_H

class RssFeedService
{
private:
	RssFeedDatabase _rssFeedDatabase;

	string getJsonString();

	char addRssFeed(vector<string>);
	char updateRssFeed(vector<string>);
	char deleteRssFeed(string);

public:
	RssFeedService();
	~RssFeedService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
