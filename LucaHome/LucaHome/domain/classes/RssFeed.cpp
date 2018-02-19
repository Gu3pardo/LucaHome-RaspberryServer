#include "RssFeed.h"

RssFeed::RssFeed()
{
	RssFeed("", "", "", 0);
}

RssFeed::RssFeed(string uuid, string title, string url, int playCount)
{
	_uuid = uuid;
	_title = title;
	_url = url;
	_playCount = playCount;
}

RssFeed::~RssFeed()
{
}

void RssFeed::SetUuid(string uuid)
{
	_uuid = uuid;
}

string RssFeed::GetUuid()
{
	return _uuid;
}

void RssFeed::SetTitle(string title)
{
	_title = title;
}

string RssFeed::GetTitle()
{
	return _title;
}

void RssFeed::SetUrl(string url)
{
	_url = url;
}

string RssFeed::GetUrl()
{
	return _url;
}

void RssFeed::SetPlayCount(int playCount)
{
	_playCount = playCount;
}

int RssFeed::GetPlayCount()
{
	return _playCount;
}

string RssFeed::JsonString()
{
	string str =
		string("{")
		+ string("\"RssFeed\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"Url\":\"") + _url + string("\",")
		+ string("\"PlayCount\":") + Tools::ConvertIntToStr(_playCount) + string("")
		+ string("}")
		+ string("}");
	return str;
}

string RssFeed::ToString()
{
	string str = string("RssFeed { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; url: ") + _url
		+ string("; playcount: ") + Tools::ConvertIntToStr(_playCount)
		+ string(" }");
	return str;
}
