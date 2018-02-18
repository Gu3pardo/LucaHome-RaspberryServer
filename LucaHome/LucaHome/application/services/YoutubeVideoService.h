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
#include "../../dataaccess/databases/YoutubeVideoDatabase.h"
#include "../../domain/classes/YoutubeVideo.h"

using namespace std;

#ifndef YOUTUBE_VIDEO_SERVICE_H
#define YOUTUBE_VIDEO_SERVICE_H

class YoutubeVideoService
{
private:
	YoutubeVideoDatabase _youtubeVideoDatabase;

	string getJsonString();

	char addYoutubeVideo(vector<string>);
	char updateYoutubeVideo(vector<string>);
	char deleteYoutubeVideo(string);

public:
	YoutubeVideoService();
	~YoutubeVideoService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
