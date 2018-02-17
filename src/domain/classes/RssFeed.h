#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef RSSFEED_H
#define RSSFEED_H

class RssFeed
{
private:
	string _uuid;
	string _title;
	string _url;
	int _playCount;

public:
	RssFeed();
	RssFeed(string, string, string, int);
	~RssFeed();

	void SetUuid(string);
	string GetUuid();

	void SetTitle(string);
	string GetTitle();

	void SetUrl(string);
	string GetUrl();

	void SetPlayCount(int);
	int GetPlayCount();

	string JsonString();
	string ToString();
};

#endif
