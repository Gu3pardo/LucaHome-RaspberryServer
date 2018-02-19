#include "RadioStream.h"

RadioStream::RadioStream()
{
	RadioStream("", "", "", 0);
}

RadioStream::RadioStream(string uuid, string title, string url, int playCount)
{
	_uuid = uuid;
	_title = title;
	_url = url;
	_playCount = playCount;
}

RadioStream::~RadioStream()
{
}

void RadioStream::SetUuid(string uuid)
{
	_uuid = uuid;
}

string RadioStream::GetUuid()
{
	return _uuid;
}

void RadioStream::SetTitle(string title)
{
	_title = title;
}

string RadioStream::GetTitle()
{
	return _title;
}

void RadioStream::SetUrl(string url)
{
	_url = url;
}

string RadioStream::GetUrl()
{
	return _url;
}

void RadioStream::SetPlayCount(int playCount)
{
	_playCount = playCount;
}

int RadioStream::GetPlayCount()
{
	return _playCount;
}

string RadioStream::JsonString()
{
	string str =
		string("{")
		+ string("\"RadioStream\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"Url\":\"") + _url + string("\",")
		+ string("\"PlayCount\":") + Tools::ConvertIntToStr(_playCount) + string("")
		+ string("}")
		+ string("}");
	return str;
}

string RadioStream::ToString()
{
	string str = string("RadioStream { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; url: ") + _url
		+ string("; playcount: ") + Tools::ConvertIntToStr(_playCount)
		+ string(" }");
	return str;
}
