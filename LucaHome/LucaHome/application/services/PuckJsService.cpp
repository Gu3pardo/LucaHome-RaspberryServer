#include "PuckJsService.h"

/*===============PUBLIC==============*/

PuckJsService::PuckJsService() {}

PuckJsService::~PuckJsService() {}

void PuckJsService::Initialize(string databaseName)
{
	_puckJsDatabase = PuckJsDatabase(databaseName);
}

string PuckJsService::PerformAction(vector<string> data)
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
		if (data.size() == PUCK_JS_DATA_SIZE)
		{
			char error = addPuckJs(data);
			if (!error)
			{
				return PUCK_JS_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"PuckJs\",\"Error\":195,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return PUCK_JS_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == PUCK_JS_DATA_SIZE)
		{
			char error = updatePuckJs(data);
			if (!error)
			{
				return PUCK_JS_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"PuckJs\",\"Error\":195,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return PUCK_JS_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deletePuckJs(actionParameter);
		if (!error)
		{
			return PUCK_JS_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "{\"Category\":\"PuckJs\",\"Error\":195,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void PuckJsService::Dispose()
{
	_puckJsDatabase.Dispose();
}

/*==============PRIVATE==============*/

string PuckJsService::getJsonString()
{
	vector<PuckJs> puckJsList = _puckJsDatabase.GetList();

	stringstream data;
	for (int index = 0; index < puckJsList.size(); index++)
	{
		data << puckJsList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"PuckJs\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char PuckJsService::addPuckJs(vector<string> newPuckJsData)
{
	PuckJs newPuckJs(
		newPuckJsData[PUCK_JS_UUID_INDEX].c_str(),
		newPuckJsData[PUCK_JS_ROOM_UUID_INDEX].c_str(),
		newPuckJsData[PUCK_JS_NAME_INDEX].c_str(),
		newPuckJsData[PUCK_JS_MAC_INDEX].c_str());
	return _puckJsDatabase.Insert(newPuckJs);
}

char PuckJsService::updatePuckJs(vector<string> updatePuckJsData)
{
	PuckJs updatePuckJs(
		updatePuckJsData[PUCK_JS_UUID_INDEX].c_str(),
		updatePuckJsData[PUCK_JS_ROOM_UUID_INDEX].c_str(),
		updatePuckJsData[PUCK_JS_NAME_INDEX].c_str(),
		updatePuckJsData[PUCK_JS_MAC_INDEX].c_str());
	return _puckJsDatabase.Update(updatePuckJs);
}

char PuckJsService::deletePuckJs(string deleteUuid)
{
	return _puckJsDatabase.Delete(deleteUuid);
}
