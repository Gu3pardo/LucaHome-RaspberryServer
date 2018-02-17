#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef RADIOSTREAM_H
#define RADIOSTREAM_H

class RadioStream
{
private:
	string _uuid;
	string _title;
	string _url;
	int _playCount;

public:
	RadioStream();
	RadioStream(string, string, string, int);
	~RadioStream();

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
