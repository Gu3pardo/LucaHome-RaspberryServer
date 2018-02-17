#include "YoutubeVideo.h"

YoutubeVideo::YoutubeVideo()
{
	_uuid = "";
	_title = "";
	_youtubeId = "";
	_playCount = 0;
	_description = "";
	_mediumImageUrl = "";
}

YoutubeVideo::YoutubeVideo(string uuid, string title, string youtubeId, int playCount, string description, string mediumImageUrl)
{
	_uuid = uuid;
	_title = title;
	_youtubeId = youtubeId;
	_playCount = playCount;
	_description = description;
	_mediumImageUrl = mediumImageUrl;
}

YoutubeVideo::~YoutubeVideo()
{
}

void YoutubeVideo::SetUuid(string uuid)
{
	_uuid = uuid;
}

string YoutubeVideo::GetUuid()
{
	return _uuid;
}

void YoutubeVideo::SetTitle(string title)
{
	_title = title;
}

string YoutubeVideo::GetTitle()
{
	return _title;
}

void YoutubeVideo::SetYoutubeId(string youtubeId)
{
	_youtubeId = youtubeId;
}

string YoutubeVideo::GetYoutubeId()
{
	return _youtubeId;
}

void YoutubeVideo::SetPlayCount(int playCount)
{
	_playCount = playCount;
}

int YoutubeVideo::GetPlayCount()
{
	return _playCount;
}

void YoutubeVideo::SetDescription(string description)
{
	_description = description;
}

string YoutubeVideo::GetDescription()
{
	return _description;
}

void YoutubeVideo::SetMediumImageUrl(string mediumImageUrl)
{
	_mediumImageUrl = mediumImageUrl;
}

string YoutubeVideo::GetMediumImageUrl()
{
	return _mediumImageUrl;
}

string YoutubeVideo::JsonString()
{
	string str =
		string("{")
		+ string("\"YoutubeVideo\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"YoutubeId\":\"") + _youtubeId + string("\",")
		+ string("\"PlayCount\":") + Tools::ConvertIntToStr(_playCount) + string(",")
		+ string("\"Description\":\"") + _description + string("\",")
		+ string("\"MediumImageUrl\":\"") + _mediumImageUrl
		+ string("}")
		+ string("}");
	return str;
}

string YoutubeVideo::ToString()
{
	string str = string("YoutubeVideo { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; youtubeid: ") + _youtubeId
		+ string("; playcount: ") + Tools::ConvertIntToStr(_playCount)
		+ string("; description: ") + _description
		+ string("; mediumimageurl: ") + _mediumImageUrl
		+ string(" }");
	return str;
}
