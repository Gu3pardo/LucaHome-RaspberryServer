#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef YOUTUBE_VIDEO_H
#define YOUTUBE_VIDEO_H

class YoutubeVideo
{
private:
	string _uuid;
	string _title;
	string _youtubeId;
	int _playCount;
	string _description;
	string _mediumImageUrl;

public:
	YoutubeVideo();
	YoutubeVideo(string, string, string, int, string, string);
	~YoutubeVideo();

	void SetUuid(string);
	string GetUuid();

	void SetTitle(string);
	string GetTitle();

	void SetYoutubeId(string);
	string GetYoutubeId();

	void SetPlayCount(int);
	int GetPlayCount();

	void SetDescription(string);
	string GetDescription();

	void SetMediumImageUrl(string);
	string GetMediumImageUrl();

	string JsonString();
	string ToString();
};

#endif
