#include "YoutubeVideoService.h"

/*===============PUBLIC==============*/

YoutubeVideoService::YoutubeVideoService() {}

YoutubeVideoService::~YoutubeVideoService() {}

void YoutubeVideoService::Initialize(string databaseName)
{
	_youtubeVideoDatabase = YoutubeVideoDatabase(databaseName);
}

string YoutubeVideoService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	else if (action == ADD)
	{
		if (data.size() == YOUTUBE_VIDEO_DATA_SIZE)
		{
			char error = addYoutubeVideo(data);
			if (!error)
			{
				return YOUTUBE_VIDEO_ADD_SUCCESS;
			}
			return YOUTUBE_VIDEO_ERROR_ADD;
		}
		return YOUTUBE_VIDEO_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == YOUTUBE_VIDEO_DATA_SIZE)
		{
			char error = updateYoutubeVideo(data);
			if (!error)
			{
				return YOUTUBE_VIDEO_UPDATE_SUCCESS;
			}
			return YOUTUBE_VIDEO_ERROR_UPDATE;
		}
		return YOUTUBE_VIDEO_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteYoutubeVideo(actionParameter);
		if (!error)
		{
			return YOUTUBE_VIDEO_DELETE_SUCCESS;
		}
		return YOUTUBE_VIDEO_ERROR_DELETE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void YoutubeVideoService::Dispose()
{
	_youtubeVideoDatabase.Dispose();
}

/*==============PRIVATE==============*/

string YoutubeVideoService::getJsonString()
{
	vector<YoutubeVideo> youtubeVideoList = _youtubeVideoDatabase.GetList();

	stringstream data;
	for (int index = 0; index < youtubeVideoList.size(); index++)
	{
		data << youtubeVideoList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"YoutubeVideo\","
		<< "\"Action\":\"Get\","
		<< "\"Error\":0,"
		<< "\"Success\":true,"
		<< "\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char YoutubeVideoService::addYoutubeVideo(vector<string> newYoutubeVideoData)
{
	YoutubeVideo newYoutubeVideo(
		newYoutubeVideoData[YOUTUBE_VIDEO_UUID_INDEX].c_str(),
		newYoutubeVideoData[YOUTUBE_VIDEO_TITLE_INDEX].c_str(),
		newYoutubeVideoData[YOUTUBE_VIDEO_ID_INDEX].c_str(),
		atoi(newYoutubeVideoData[YOUTUBE_VIDEO_PLAY_COUNT_INDEX].c_str()),
		newYoutubeVideoData[YOUTUBE_VIDEO_DESCRIPTION_INDEX].c_str(),
		newYoutubeVideoData[YOUTUBE_VIDEO_MEDIUM_IMAGE_URL_INDEX].c_str());
	return _youtubeVideoDatabase.Insert(newYoutubeVideo);
}

char YoutubeVideoService::updateYoutubeVideo(vector<string> updateYoutubeVideoData)
{
	YoutubeVideo updateYoutubeVideo(
		updateYoutubeVideoData[YOUTUBE_VIDEO_UUID_INDEX].c_str(),
		updateYoutubeVideoData[YOUTUBE_VIDEO_TITLE_INDEX].c_str(),
		updateYoutubeVideoData[YOUTUBE_VIDEO_ID_INDEX].c_str(),
		atoi(updateYoutubeVideoData[YOUTUBE_VIDEO_PLAY_COUNT_INDEX].c_str()),
		updateYoutubeVideoData[YOUTUBE_VIDEO_DESCRIPTION_INDEX].c_str(),
		updateYoutubeVideoData[YOUTUBE_VIDEO_MEDIUM_IMAGE_URL_INDEX].c_str());
	return _youtubeVideoDatabase.Update(updateYoutubeVideo);
}

char YoutubeVideoService::deleteYoutubeVideo(string deleteUuid)
{
	return _youtubeVideoDatabase.Delete(deleteUuid);
}
