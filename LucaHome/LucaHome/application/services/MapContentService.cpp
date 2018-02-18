#include "MapContentService.h"

/*===============PUBLIC==============*/

MapContentService::MapContentService() {}

MapContentService::~MapContentService() {}

void MapContentService::Initialize(string databaseName)
{
	_mapContentDatabase = MapContentDatabase(databaseName);
}

string MapContentService::PerformAction(vector<string> data)
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
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			char error = addMapContent(data);
			if (!error)
			{
				return MAP_CONTENT_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MAP_CONTENT_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			char error = updateMapContent(data);
			if (!error)
			{
				return MAP_CONTENT_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MAP_CONTENT_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteMapContent(actionParameter);
		if (!error)
		{
			return MAP_CONTENT_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MapContentService::Dispose()
{
	_mapContentDatabase.Dispose();
}

/*==============PRIVATE==============*/

string MapContentService::getJsonString()
{
	vector<MapContent> mapContentList = _mapContentDatabase.GetList();

	stringstream data;
	for (int index = 0; index < mapContentList.size(); index++)
	{
		data << mapContentList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char MapContentService::addMapContent(vector<string> newMapContentData)
{
	Position newPosition(
		atoi(newMapContentData[MAP_CONTENT_COORDINATES_X_INDEX].c_str()),
		atoi(newMapContentData[MAP_CONTENT_COORDINATES_Y_INDEX].c_str()));
	MapContent newMapContent(
		newMapContentData[MAP_CONTENT_UUID_INDEX].c_str(),
		newMapContentData[MAP_CONTENT_TYPE_UUID_INDEX].c_str(),
		newMapContentData[MAP_CONTENT_TYPE_INDEX].c_str(),
		newPosition,
		newMapContentData[MAP_CONTENT_NAME_INDEX].c_str(),
		newMapContentData[MAP_CONTENT_SHORT_NAME_INDEX].c_str(),
		atoi(newMapContentData[MAP_CONTENT_VISIBILITY_INDEX].c_str()) == 1);
	return _mapContentDatabase.Insert(_mapContentDatabase.GetList().size(), newMapContent);
}

char MapContentService::updateMapContent(vector<string> updateMapContentData)
{
	Position updatePosition(
		atoi(updateMapContentData[MAP_CONTENT_COORDINATES_X_INDEX].c_str()),
		atoi(updateMapContentData[MAP_CONTENT_COORDINATES_Y_INDEX].c_str()));
	MapContent updateMapContent(
		updateMapContentData[MAP_CONTENT_UUID_INDEX].c_str(),
		updateMapContentData[MAP_CONTENT_TYPE_UUID_INDEX].c_str(),
		updateMapContentData[MAP_CONTENT_TYPE_INDEX].c_str(),
		updatePosition,
		updateMapContentData[MAP_CONTENT_NAME_INDEX].c_str(),
		updateMapContentData[MAP_CONTENT_SHORT_NAME_INDEX].c_str(),
		atoi(updateMapContentData[MAP_CONTENT_VISIBILITY_INDEX].c_str()) == 1);
	return _mapContentDatabase.Update(updateMapContent);
}

char MapContentService::deleteMapContent(string deleteUuid)
{
	return _mapContentDatabase.Delete(deleteUuid);
}
