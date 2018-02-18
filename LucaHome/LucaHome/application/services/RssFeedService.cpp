#include "RssFeedService.h"

/*===============PUBLIC==============*/

RssFeedService::RssFeedService() {}

RssFeedService::~RssFeedService() {}

void RssFeedService::Initialize(string databaseName)
{
	_rssFeedDatabase = RssFeedDatabase(databaseName);
}

string RssFeedService::PerformAction(vector<string> data)
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
		if (data.size() == RSS_FEED_DATA_SIZE)
		{
			char error = addRssFeed(data);
			if (!error)
			{
				return RSS_FEED_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return RSS_FEED_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == RSS_FEED_DATA_SIZE)
		{
			char error = updateRssFeed(data);
			if (!error)
			{
				return RSS_FEED_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return RSS_FEED_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteRssFeed(actionParameter);
		if (!error)
		{
			return RSS_FEED_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void RssFeedService::Dispose()
{
	_rssFeedDatabase.Dispose();
}

/*==============PRIVATE==============*/

string RssFeedService::getJsonString()
{
	vector<RssFeed> rssFeedList = _rssFeedDatabase.GetList();

	stringstream data;
	for (int index = 0; index < rssFeedList.size(); index++)
	{
		data << rssFeedList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char RssFeedService::addRssFeed(vector<string> newRssFeedData)
{
	RssFeed newRssFeed(
		newRssFeedData[RSS_FEED_UUID_INDEX].c_str(),
		newRssFeedData[RSS_FEED_TITLE_INDEX].c_str(),
		newRssFeedData[RSS_FEED_URL_INDEX].c_str(),
		atoi(newRssFeedData[RSS_FEED_PLAY_COUNT_INDEX].c_str()));
	return _rssFeedDatabase.Insert(_rssFeedDatabase.GetList().size(), newRssFeed);
}

char RssFeedService::updateRssFeed(vector<string> updateRssFeedData)
{
	RssFeed updateRssFeed(
		updateRssFeedData[RSS_FEED_UUID_INDEX].c_str(),
		updateRssFeedData[RSS_FEED_TITLE_INDEX].c_str(),
		updateRssFeedData[RSS_FEED_URL_INDEX].c_str(),
		atoi(updateRssFeedData[RSS_FEED_PLAY_COUNT_INDEX].c_str()));
	return _rssFeedDatabase.Update(updateRssFeed);
}

char RssFeedService::deleteRssFeed(string deleteUuuid)
{
	return _rssFeedDatabase.Delete(deleteUuuid);
}
