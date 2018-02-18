#include "MediaServerService.h"

/*===============PUBLIC==============*/

MediaServerService::MediaServerService() {}

MediaServerService::~MediaServerService() {}

void MediaServerService::Initialize(string databaseName)
{
	_mediaServerDatabase = MediaServerDatabase(databaseName);
}

string MediaServerService::PerformAction(vector<string> data)
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
		if (data.size() == MEDIA_SERVER_DATA_SIZE)
		{
			char error = addMediaServer(data);
			if (!error)
			{
				return MEDIA_SERVER_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MEDIA_SERVER_ERROR_WRONG_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MEDIA_SERVER_DATA_SIZE)
		{
			char error = updateMediaServer(data);
			if (!error)
			{
				return MEDIA_SERVER_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MEDIA_SERVER_ERROR_WRONG_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteMediaServer(actionParameter);
		if (!error)
		{
			return MEDIA_SERVER_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MediaServerService::Dispose()
{
	_mediaServerDatabase.Dispose();
}

/*==============PRIVATE==============*/

string MediaServerService::getJsonString()
{
	vector<MediaServer> mediaServerList = _mediaServerDatabase.GetList();

	stringstream data;
	for (int index = 0; index < mediaServerList.size(); index++)
	{
		data << mediaServerList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char MediaServerService::addMediaServer(vector<string> newMediaServerData)
{
	MediaServer newMediaServer(
		newMediaServerData[MEDIA_SERVER_UUID_INDEX].c_str(),
		newMediaServerData[MEDIA_SERVER_ROOM_UUID_INDEX].c_str(),
		newMediaServerData[MEDIA_SERVER_IP_INDEX].c_str(),
		atoi(newMediaServerData[MEDIA_SERVER_IS_SLEEPING_SERVER_INDEX].c_str()) == 1,
		newMediaServerData[MEDIA_SERVER_WIRELESS_SOCKET_UUID].c_str());
	return _mediaServerDatabase.Insert(_mediaServerDatabase.GetList().size(), newMediaServer);
}

char MediaServerService::updateMediaServer(vector<string> updateMediaServerData)
{
	MediaServer updateMediaServer(
		updateMediaServerData[MEDIA_SERVER_UUID_INDEX].c_str(),
		updateMediaServerData[MEDIA_SERVER_ROOM_UUID_INDEX].c_str(),
		updateMediaServerData[MEDIA_SERVER_IP_INDEX].c_str(),
		atoi(updateMediaServerData[MEDIA_SERVER_IS_SLEEPING_SERVER_INDEX].c_str()) == 1,
		updateMediaServerData[MEDIA_SERVER_WIRELESS_SOCKET_UUID].c_str());
	return _mediaServerDatabase.Update(updateMediaServer);
}

char MediaServerService::deleteMediaServer(string deleteUuid)
{
	return _mediaServerDatabase.Delete(deleteUuid);
}
